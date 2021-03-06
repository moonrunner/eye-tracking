/*****************************************************************************
 *   Non-Rigid Face Tracking
 ******************************************************************************
 *   by Jason Saragih, 5th Dec 2012
 *   http://jsaragih.org/
 ******************************************************************************
 *   Ch6 of the book "Mastering OpenCV with Practical Computer Vision Projects"
 *   Copyright Packt Publishing 2012.
 *   http://www.packtpub.com/cool-projects-with-opencv/book
 *****************************************************************************/
/*
 train_face_detector: learn a face_detector object from training data
 Jason Saragih (2012)
 */

#include "opencv_hotshots/ft/ft.hpp"

#define fl at<float>
const char* usage =
"usage: ./train_face_detector detector_file annotation_file shape_model_file"
" detector_model_file [-f min_frac_of_pts_in_det_rect] [--mirror]";
//==============================================================================
bool
parse_help(int argc,char** argv)
{
    for(int i = 1; i < argc; i++){
        string str = argv[i];
        if(str.length() == 2){if(strcmp(str.c_str(),"-h") == 0)return true;}
        if(str.length() == 6){if(strcmp(str.c_str(),"--help") == 0)return true;}
    }return false;
}
//==============================================================================
int
parse_frac(int argc,char** argv)
{
    for(int i = 1; i < argc; i++){
        string str = argv[i];
        if(str.length() != 2)continue;
        if(strcmp(str.c_str(),"-f") == 0){
            if(argc > i+1)return atof(argv[i+1]);
        }
    }return 0.8;
}
//==============================================================================
bool
parse_mirror(int argc,char** argv)
{
    for(int i = 1; i < argc; i++){
        string str = argv[i];
        if(str.length() != 8)continue;
        if(strcmp(str.c_str(),"--mirror") == 0)return true;
    }return false;
}
//==============================================================================
int main(int argc,char** argv)
{
    //parse cmdline input
    if(argc < 3){ cout << usage << endl; return 0;}
    float frac = parse_frac(argc,argv);
    bool mirror = parse_mirror(argc,argv);
    
    //load data
    if (argc<2) {
        return 0;
    }
    string fname =string(argv[2]);
    ft_data  ftdata = load_ft_jzp(fname);
    
    shape_model smodel = load_ft<shape_model>(string(ftdata.baseDir+"shapemodel.yaml").c_str());
    smodel.set_identity_params();
    vector<Point2f> r = smodel.calc_shape();
    Mat ref = Mat(r).reshape(1,2*r.size());
    
    //train face detector
    face_detector detector;
    
    //copy the haar detector file to the workspace.
    string haardetector = argv[1];
    string detectorName;
    if (haardetector.find_last_of("/\\") ==string::npos)
        detectorName = haardetector;
    else
        detectorName= haardetector.substr(haardetector.find_last_of("/\\"),haardetector.length());
//    cout<<detectorName<<endl;
    std::ifstream  src(haardetector, std::ios::binary);
    std::ofstream  dst(ftdata.baseDir+detectorName,   std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();
    
    detector.train(ftdata,argv[1],ref,mirror,true,frac);
    //save detector
    save_ft<face_detector>(string(ftdata.baseDir+"detectormodel.yaml").c_str(),detector);
    return 0;
}
//==============================================================================
