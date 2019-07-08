class Matrix
{
    public: 
        int row;  //行
        int col;  //列
        double** p_top; //配列の最初を指すポインタ

    public:
        Matrix(int i=1, int j=1);//コンストラクタ
        Matrix(const Matrix &cp);//コピーコンストラクタ

        ~Matrix();//デストラクタ

        int row_size(){return(row);}
        int col_size(){return(col);}

        void change_size(int i, int j);//サイズ変更

        //演算子オーバーロード
        double* &operator[](int i){ return(p_top[i]); }
        Matrix operator=(const Matrix &a);
        Matrix operator+(const Matrix &a);
        Matrix operator-(const Matrix &a);
        Matrix operator*(const Matrix &a);

        friend Matrix operator*(const Matrix &a, double b);
        friend Matrix operator*(double b, const Matrix &a);

        //行列変換
        void unit_matrix();//単位行列
        Matrix transposed();//転置行列
};