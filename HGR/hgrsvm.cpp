#include "hgrsvm.h"

using namespace cv;
using namespace std;
HGRSVM::HGRSVM()
{
}

void HGRSVM::fillTab ( int nb, string pathFile, float label, float trainingData[][100], float labels[] ) {

    int nbNewLine = 0;
    ifstream fichier( pathFile.c_str(), ios::in );

    string line;

    if ( !fichier )
        cout << "fichier inexistant";
    else
    {
        while( !fichier.eof() )
        {
            getline(fichier, line);
            for( unsigned int i = 0 ; i < line.length() ; i++ )
                trainingData[nb + nbNewLine][i] = line.at(i) - 48;
            nbNewLine++;
        }
    }

    for( int i = nb ; i < nbNewLine + nb ; i++ )
        labels[i] = label;

    fichier.close();
}








void HGRSVM::train( int nbRegionByLine, int nbFrame, int nbRegion ) {

//    float **trainingData = new float*[nbFrame];
//    for (int i = 0 ; i < nbFrame ; i++)
//        trainingData[i] = new float[nbRegion];
     float trainingData[nbFrame][100];
    float labels[nbFrame];
    // fillTables();

    fillTab ( 0, "../res/label0.txt", 0.0, trainingData, labels );
    fillTab ( nbFrame/5, "../res/label1.txt", 1.0, trainingData, labels );
    fillTab ( 2*nbFrame/5, "../res/label2.txt", 2.0, trainingData, labels );
    fillTab ( 3*nbFrame/5, "../res/label3.txt", 3.0, trainingData, labels );
    fillTab ( 4*nbFrame/5, "../res/labelN.txt", -1.0, trainingData, labels );

    Mat trainingDataMat(nbFrame, nbRegionByLine*nbRegionByLine, CV_32FC1, trainingData);
    Mat labelsMat(nbFrame, 1, CV_32FC1, labels);

    // Set up SVM's parameters
    CvSVMParams params;
    params.svm_type    = CvSVM::C_SVC;
    params.kernel_type = SVM::LINEAR;
    params.degree = 3.43; // for poly
    params.gamma = 0.00225; // for poly / rbf / sigmoid
    params.coef0 = 19.6; // for poly / sigmoid
    params.C = 0.5; // for CV_SVM_C_SVC , CV_SVM_EPS_SVR and CV_SVM_NU_SVR
    params.nu = 0.0; // for CV_SVM_NU_SVC , CV_SVM_ONE_CLASS , and CV_SVM_NU_SVR
    params.p = 0.0; // for CV_SVM_EPS_SVR
    params.class_weights = NULL; // for CV_SVM_C_SVC
    params.term_crit.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;
    params.term_crit.max_iter = 1000;
    params.term_crit.epsilon = 1e-6;

    // Train the SVM
    CvSVM SVM;
    SVM.train( trainingDataMat, labelsMat, Mat(), Mat(), params);
    SVM.save( "model.txt" );
}

float HGRSVM::createPredictedData( string line, int nbRegionByLine) {

    CvSVM cvSvm;
    cvSvm.load("model.txt");

    int nbRegion = nbRegionByLine*nbRegionByLine;
    float data[1][nbRegion];
    for (unsigned int i = 0 ; i < line.size() ; i++)
        data[0][i] = line.at(i) - 48 ;

    Mat dataMat( 1, nbRegion, CV_32FC1, data );

    return cvSvm.predict(dataMat);
}

HGRSVM::~HGRSVM(){

}
