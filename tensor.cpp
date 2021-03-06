//
// Created by Mayank Parasar on 2020-03-09.
//


/* tensor dim are (10, 4, 5) */
#include <iostream>
#include <vector>


using namespace std;

class Tensor {
public:
    Tensor() {

    }
    ~Tensor() {
        cout << endl << "Call to the destructor of Tensor" << endl;
        free(tensor_);
        cout << " Freed the memory pointed by the member variable of the object pointer of Tensor" << endl;
    }
    void create_tensor(vector<int> size);
    void initialize_tensor(double arr[]);

    void multiply_row_tensor(vector<double> row);
    void multiply_scalar_tensor(double val);
    void multiply_matrix_tensor(vector<vector<double>> mat);
    void print_tensor();
    vector<int>& get_size() { return size;}; // this can be used to set-size as well

    int get_total_elem() { return total_elem; };
private:
    vector<int> size;
    int total_elem;
    double * tensor_;

};

void
Tensor::create_tensor(vector<int> size) {
    int total_size = 1;

    for(auto i : size) {
        total_size *= i;
    }
    total_elem = total_size;
    // allocate memory for the tensor
    // and put it in the member variable tensor
    tensor_ = (double*) malloc(sizeof(double)*total_size); // this does not give error!!
//    tensor_ =  new double(sizeof(double)*total_size); // this gives memory error!! (why?)

    return;
}

void
Tensor::initialize_tensor(double arr[]) {

    for(int ii=0; ii < total_elem ; ii++) {
        tensor_[ii] = arr[ii];
    }
}

void
Tensor::multiply_row_tensor(vector<double> row) {
    int num_mult = 0;
    for(int ii = 0; ii < total_elem; ii += row.size()) {
        for(int jj = 0; jj < row.size(); jj++) {
            tensor_[ii+jj] *= row[jj];
        }
        num_mult++;
    }
    cout << endl << "num multiplications: " << num_mult << endl;
}


void
Tensor:: multiply_matrix_tensor(vector<vector<double>> mat) {
    int row = mat.size();
    int col = mat[0].size();
    for(int ii = 0; ii < total_elem; ii += row*col) {
        for(int jj = 0; jj < row; jj++) {  // row
            for(int kk = 0; kk < col; kk++) {  // col
                tensor_[ii+row*kk+jj] *= mat[jj][kk];
            }
        }
    }
}

void
Tensor::print_tensor() {

    for(int ii=0; ii < total_elem ; ii++) {
        cout << tensor_[ii] << " ";
    }
}


void
Tensor::multiply_scalar_tensor(double val) {
    for(int ii = 0; ii < total_elem; ii ++) {
        tensor_[ii] *= val;
    }
}

int main() {

    Tensor * t = new Tensor();

    t->get_size() = {10, 4, 5}; // the getter func gives the reference to set the size vector
    t->create_tensor(t->get_size());

    // iniitalize tensor
    double arr[t->get_total_elem()];

    for(int ii=0; ii < t->get_total_elem(); ii++) {
        arr[ii] = 1.25;
    }

//    for(int ii=0; ii < t->total_space; ii++) {
//        cout << arr[ii] << " ";
//    }

    t->initialize_tensor(arr);

    t->print_tensor();

    vector<double> row(10, (double)2.0);
    t->multiply_row_tensor(row);
    cout << endl;

    t->print_tensor();

    t->multiply_scalar_tensor((double)3.0);
    cout << endl;
    t->print_tensor();

    vector<vector<double>>matrix = {{3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0},
                                    {3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0},
                                    {3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0},
                                    {3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0}};

    t->multiply_matrix_tensor(matrix);
    cout << endl;
    t->print_tensor();
    t->~Tensor();  // should not call explicit destructor
    free(t);
    cout << endl<< "after freeing the object pointer 't'" << endl;

    return 0;
}