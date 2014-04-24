#include "hgrsvm.h"

using namespace cv;
using namespace std;
HGRSVM::HGRSVM()
{
    totalLine = 0;
}

vector<string> & HGRSVM::split( const string &s, char delim, vector<string> &elems ) {

    stringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

vector<string> HGRSVM::split( const string &s, char delim ) {

    vector<string> elems;
    split(s, delim, elems);

    return elems;
}

void HGRSVM::loadLabels( string resourcesPath, float trainingData[][100], float labels[] ) {

    DIR *dir = opendir( resourcesPath.c_str() );

    if ( dir == NULL )
    {
        cout << "Impossible to list directory" << endl;
        exit(0);
    }
    else
    {
        struct dirent *ent;
        vector<string> expFilename;
        int label;

        while ( (ent = readdir( dir )) != NULL )
        {
            string filename (ent->d_name);
            if (!filename.compare(".") || !filename.compare(".."))
                continue;
            expFilename = split( filename, '_' );
            label = atoi( expFilename.at(1).c_str() );
            fillTab( resourcesPath + filename, label, trainingData, labels );
        }

        closedir(dir);
    }
}

int HGRSVM::getNbFrame( string resourcesPath ) {

    DIR *dir = opendir( resourcesPath.c_str() );
    int nbFrame = 0;
    string filePath;
    string line;

    if ( dir == NULL )
    {
        cout << "Impossible to list directory" << endl;
        exit(0);
    }
    else
    {
        struct dirent *ent;

        while ( (ent = readdir( dir )) != NULL )
        {
            string filename (ent->d_name);
            if (!filename.compare(".") || !filename.compare(".."))
                continue;

            filePath = resourcesPath + filename;

            ifstream fichier( filePath.c_str(), ios::in );
            if ( !fichier )
                cout << "fichier inexistant";
            else {
                getline( fichier, line );
                nbFrame += atoi(line.c_str());
            }
            fichier.close();
        }
        closedir(dir);
    }

    return nbFrame;
}

void HGRSVM::fillTab( string pathFile, float label, float trainingData[][100], float labels[] ) {

    int nbNewLine = 0;
    ifstream fichier( pathFile.c_str(), ios::in );

    string line;

    if ( !fichier )
        cout << "fichier inexistant";
    else
    {
        getline(fichier, line); // Pour lire le nombre de frame
        while( !fichier.eof() )
        {
            getline(fichier, line);
            for( unsigned int i = 0 ; i < line.length() ; i++ ) {
                trainingData[totalLine + nbNewLine][i] = line.at(i) - 48; //Tester avec atoi(line.at(i).c_str)
            }
            nbNewLine++;
        }
    }

    for( int i = totalLine ; i < nbNewLine + totalLine ; i++ )
        labels[i] = label;

    totalLine += nbNewLine - 1;

    fichier.close();
}

void HGRSVM::train( int nbRegion ) {

    (void)nbRegion;
    int nbRegionByLine = sqrt(nbRegion);

//    float **trainingData = new float*[nbFrame];
//    for (int i = 0 ; i < nbFrame ; i++)
//        trainingData[i] = new float[nbRegion];

    int nbFrame = getNbFrame( "../res/" );

    float trainingData[nbFrame][100];
    float labels[nbFrame];

    loadLabels( "../res/", trainingData, labels );

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

float HGRSVM::createPredictedData( CvSVM &cvSvm, string line, int nbRegionByLine) {

    //CvSVM cvSvm;
    //cout << "Before load model" << endl;
    //cvSvm.load("model.txt");
    //cout << "After load model" << endl;

    int nbRegion = nbRegionByLine*nbRegionByLine;
    float data[1][nbRegion];
    for (unsigned int i = 0 ; i < line.size() ; i++)
        data[0][i] = line.at(i) - 48 ;

    Mat dataMat( 1, nbRegion, CV_32FC1, data );

    return cvSvm.predict(dataMat);
}

HGRSVM::~HGRSVM(){

}
