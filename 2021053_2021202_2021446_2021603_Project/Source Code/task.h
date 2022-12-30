#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<time.h>
#include<algorithm>
using namespace std;

//class declaration
class data_clustering
{

    public:
    int row;
      int column;
      //2d array storing data matrix elements
      double**array;
      double **graph_array;
      //2d correlation matrix
      double**corelation_matrix;
      vector<vector<int>> bitmap;
      //1d signature array storing signature values of each row
      double*signature_array;
      //1d node array that is storing weights of each node
      double*node_array;
      //2d vector that is storing clusters
      vector<vector<int>>cluster_array;
      //bool array that is checking weather a given node has been included in cluster or not
      bool*cluster_check;
      double *meancolumn_array;
      int counter;
      //constructor

      data_clustering();

      //function that is getting data from file and storing them in array
void get_data()
{
    fstream my_file;
    //file reading
    my_file.open("data.txt",ios::in);


    int line =1;
    int row_count=0;
    if(my_file.is_open())
            {
        //loop runs till end of file
    while(!my_file.eof())
    {
        counter = 0;
        string line_data;
        getline(my_file,line_data);
        //first line condition
        if(line==1)
        {

            row=stoi(line_data);

            array=new double*[row];

        }
        //second line condition
        else if(line==2)
        {
            column=stoi(line_data);
            for(int i=0;i<row;i++)
            {
                array[i]=new double[column];
            }
        }
        //4th line onward condition.For each line 4 elements will be stored in correlation matrix
        else if(line>3){



            string element={NULL};
            int i=0;
            int j=0;
            //loop runs till the end of a particular line
            while(line_data[i]!='\0')
            {

                //conditions that separates elements from each other
                if(line_data[i+1]=='\t'||line_data[i+1]=='\0')
                {
                    element+=line_data[i];
                   element[0]='0';

                   double element2=stod(element);
                   array[row_count][j]=element2;
                   i+=2;
                   element={NULL};
                   if(j==3)
                   {
                    break;
                   }
                   j++;

                }
                else{
                element+=line_data[i];
                i++;

                }

            }

            row_count++;
            line_data.clear();



        }
            line++;
    }
    }

    my_file.close();




}
//funtion to set correlation values of all rows
void correlationMatrix()
{
   corelation_matrix=new double*[row];
   for(int i=0;i<row;i++)
   {
    corelation_matrix[i]=new double[row];
   }
   for(int i=0;i<row;i++)
   {
    for(int j=0;j<row;j++)
    {
        corelation_matrix[i][j]=upper_part(i,j)/lower_part(i,j);
    }
   }


}
//function to print data matrix array
void print_array()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            cout<<'('<<array[i][j]<<")";
        }

    }
}

//upper part of formula of pearsons correlation coefficient
double upper_part(int row1,int row2)
{
    double answer=0;
    for(int i=0;i<column;i++)
    {
        answer+=((array[row1][i]-mean(row1))*(array[row2][i]-mean(row2)));
    }
    return answer;
}

//lower part of formula of pearsons correlation coefficient
double lower_part(int row1,int row2)
{
   double xtotal=0;
   double ytotal=0;
   for(int i=0;i<column;i++)
   {
    xtotal+=((array[row1][i]-mean(row1))*(array[row1][i]-mean(row1)));
     ytotal+=((array[row2][i]-mean(row2))*(array[row2][i]-mean(row2)));
   }
   double total=xtotal*ytotal;
   total=sqrt(total);
   return total;
}

//function to fine mean value of row elements of data matrix
double mean(int row1)
{

   double total= sum_row_elements(row1);
    return total/double(column);
}

//swapping rows of data matrix function
double sum_row_elements(int row1)
{
    double sum=0;
   for(int i=0;i<column;i++)
   {
     sum+=array[row1][i];
   }

   return sum;

}

//swapping rows of data matrix function
void swap_rows(int row1,int row2)
{
   for(int i=0;i<column;i++)
   {
    double temp=array[row1][i];
    array[row1][i]=array[row2][i];
    array[row2][i]=temp;
   }



}

//function to store signature values of all rows in 1D signature array
void signatureArrayFunction()
{
    signature_array=new double[row];

    for(int i=0;i<row;i++)
    {
        signature_array[i]=signature_value(i);
    }
}

//function to permute data matrix by swapping almost each data matrix row with (rand%row) row where rand is random number
void permute_data_matrix()
{


   for(int i=0;i<row;i++)
   {
    int x=rand()%row;
    if(i!=x)
    {
        swap_rows(i,x);
    }
   }
}

//function to recover data matrix by assigning position to rows with respect to their signature value
void rearrangeFunction()
{
   for(int i=0;i<row;i++)
   {
    for(int j=i+1;j<row;j++)
    {
        if(signature_array[i]>signature_array[j])
        {
            swap(signature_array[i],signature_array[j]);
            swap_rows(i,j);
        }
    }
   }
}

//function to find signature value of each row
double signature_value(int row)
{
    double total=sum_row_elements(row);
    double mean_=mean(row);
    return total*mean_;
}


//function to find mean of column elements to be used as a threshold for bit map
double mean_column(int column)
{
    double total=0;
    for(int i=0;i<row;i++)
    {
        total+=corelation_matrix[i][column];
    }

    return total/double(row);
}

// function to update correlation matrix
void update_corelation()
{
    bitmap.resize(row);
   for(int i = 0; i < row; i++)
   {
       bitmap[i].resize(row);
   }
   meancolumn_array=new double[row];
       for(int i=0;i<row;i++)
       {
           meancolumn_array[i]=mean_column(i);
       }

       for(int i=0;i<row;i++)
       {
           for(int j=0;j<row;j++)
           {
               if(corelation_matrix[j][i]<=meancolumn_array[i])
               {
                      corelation_matrix[i][j]=0;
               }
               else{
                   corelation_matrix[i][j]=1;
               }

           }
       }

       for(int i=0;i<row;i++)
       {
           for(int j=0;j<row;j++)
           {
               bitmap[i][j] = corelation_matrix[i][j];
           }
       }

}

double max_column_elements(int colum)
{
    double max=0;
    for(int i=0;i<row;i++)
    {
        if(max<corelation_matrix[i][colum]&&corelation_matrix[i][colum]!=1)
        {
            max=corelation_matrix[i][colum];
        }
    }
    return max;
}

//function that is enabling color coding
  void update_correlation_for_green_shade()
  {
      correlationMatrix();
    for(int colum=0;colum<row;colum++)
    {
        //max_column storing maximum column element
        double max_column=max_column_elements(colum);
        for(int ro=0;ro<row;ro++)
        {
            //condition as defined in project guidelines
            if(corelation_matrix[ro][colum]==1)
            {
                corelation_matrix[ro][colum]=255;
            }
            else
            {
            corelation_matrix[ro][colum]=(corelation_matrix[ro][colum]/max_column)*255;
            }
        }
    }

  }

  //function that will check weather all clusters have been created or not
   bool cluster_complete_check()
   {
      bool answer=true;
      for(int i=0;i<row;i++)
      {
        if(cluster_check[i]==false)
        {
            answer=false;
        }
      }
    return answer;
   }

   //function returning index of node having max weight and one that is not in cluster
  int max_weight_index()
  {
     double max=-2;
     int index=0;

     for( int i=0;i<row;i++)
     {
        if(max<node_array[i]&&cluster_check[i]==0)
        {
            max=node_array[i];
            index=i;
        }
     }
     return index;
  }
  void clustering()
  {
      //function that will run till all clusters have been created
      for(int i = 0; i < cluster_array.size(); i++)
      {
          cluster_array[i].clear();
      }
      cluster_array.clear();
      counter = 0;
      cluster_array.resize(0);


      //function that will run till all clusters have been created
           while(!cluster_complete_check())
           {
             int value=max_weight_index();
             cluster_array.resize(counter+1);
             //loop to find edges connected to max weight node
             for(int i=0;i<row;i++)
             {
                 //condition that will connect nodes and hence make cluster
                 if(graph_array[value][i]!=30000&&cluster_check[i]==0)
                 {

                     cluster_array[counter].push_back(i);

                     cluster_check[i]=1;
                 }
             }
             counter++;
             cluster_check[value]=1;
           }
           cout << "Done\n";

  }

  // weighed graph function
   void weighted_graph(double value)
   {
       //correlation matrix created
       correlationMatrix();

       //graph array is actually the graph storing corelation matrix elements
             graph_array=new double*[row];
             for(int i=0;i<row;i++)
             {
               graph_array[i]=new double[row];
             }

             //removing edges lieing below value.Value is acting as a thrershold
             for(int i=0;i<row;i++)
             {
               for(int j=0;j<row;j++)
               {
                   graph_array[i][j]=corelation_matrix[i][j];
               }
             }

             while(value<-1||value>=1)
             {
                 return;

             }

             for(int i=0;i<row;i++)
             {
               for(int j=0;j<row;j++)
               {
                   if(graph_array[i][j]<value)
                   {
                       graph_array[i][j]=30000;
                   }
               }
             }

             node_array=new double[row];
             //storing all node weights in array

             for(int i=0;i<row;i++)
             {
               double node_weight=0;
               for(int j=0;j<row;j++)
               {

                   if(graph_array[i][j]!=30000)
                   {
                  node_weight+=graph_array[i][j];
                   }

               }
               node_array[i]=node_weight;
             }

             cluster_check=new bool[row];
             for(int i=0;i<row;i++)
             {

               cluster_check[i]=false;
             }

   }

};

#endif // TASK_H


