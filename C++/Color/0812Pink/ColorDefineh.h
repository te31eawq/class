
#pragma once

#define _USE_OPENCV_4100_

#ifdef _USE_OPENCV_4100_
	#include <opencv2/opencv.hpp>
#endif // _USE_OPENCV_4100


#ifdef _USE_OPENCV_4100_
	#ifdef _DEBUG
		#pragma comment(lib, "opencv_world4100d.lib")
	#else
		#pragma comment(lib, "opencv_world4100.lib")
	#endif // _DEBUG
#endif // _USE_OPENCV_4100_

