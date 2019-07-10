class Matrix
{
public: 
    int row;  //行
    int col;  //列
    double** p_top; //配列の最初を指すポインタ

public:
    // コンストラクタ
    Matrix(int i=1, int j=1);
    // コピーコンストラクタ
    Matrix(const Matrix &cp);
    // デストラクタ
    ~Matrix();

    int row_size(){return(row);}
    int col_size(){return(col);}

    // 行列要素の初期化
    void Matrix::convertMatrix(double **target, Matrix *output);

    // リサイズ
    void change_size(int i, int j);

    //演算子オーバーロード
    double* &operator[](int i){return(p_top[i]);}
    Matrix operator=(const Matrix &a); // 代入
    Matrix operator+(const Matrix &a); // 加算
    Matrix operator-(const Matrix &a); // 減算
    Matrix operator*(const Matrix &a); // 乗算
    friend Matrix operator*(const Matrix &a, double b); // 乗算(pattern1)
    friend Matrix operator*(double b, const Matrix &a); // 乗算(pattern2)

    //単位行列
    void unit_matrix();
    //転置行列
    Matrix transposed();
};