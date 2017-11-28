#include "utils.hpp"

namespace VISG {
	/*
	*brief: convert sl Mat to cv Mat
	*/
	cv::Mat slMat2cvMat(sl::Mat& input) {
		// Mapping between MAT_TYPE and CV_TYPE
		int cv_type = -1;
		switch (input.getDataType()) {
		case sl::MAT_TYPE_32F_C1: cv_type = CV_32FC1; break;
		case sl::MAT_TYPE_32F_C2: cv_type = CV_32FC2; break;
		case sl::MAT_TYPE_32F_C3: cv_type = CV_32FC3; break;
		case sl::MAT_TYPE_32F_C4: cv_type = CV_32FC4; break;
		case sl::MAT_TYPE_8U_C1: cv_type = CV_8UC1; break;
		case sl::MAT_TYPE_8U_C2: cv_type = CV_8UC2; break;
		case sl::MAT_TYPE_8U_C3: cv_type = CV_8UC3; break;
		case sl::MAT_TYPE_8U_C4: cv_type = CV_8UC4; break;
		default: break;
		}

		// Since cv::Mat data requires a uchar* pointer, we get the uchar1 pointer from sl::Mat (getPtr<T>())
		// cv::Mat and sl::Mat will share a single memory structure
		return cv::Mat(input.getHeight(), input.getWidth(), cv_type, input.getPtr<sl::uchar1>(sl::MEM_CPU));
	}
	/*
	*brief: show stereo image left and right
	*/
	void imshow(const std::string &name, const cv::Mat &left, const cv::Mat &right) {
		cv::Size left_size = left.size();
		cv::Size right_size = right.size();

		cv::Size size(left_size.width + right_size.width, left_size.height);
		cv::Mat large(size, left.type());
		large.setTo(0);
		cv::Mat img1 = large(cv::Rect(0, 0, left_size.width, left_size.height));
		cv::Mat img2 = large(cv::Rect(left_size.width, 0, right_size.width, left_size.height));
		left.copyTo(img1);
		right.copyTo(img2);

		cv::imshow(name, large);
	}

	/*
	* brief: convert depth to image to save
	*/

	void depth2Image(const cv::Mat& depth, cv::Mat &depth_image) {
		for (int i = 0; i < depth.rows; ++i) {
			const float *p = depth.ptr<float>(i);
			uchar *q = depth_image.ptr<uchar>(i);
			for (int j = 0; j < depth.cols; ++j) {
				//std::cout << "p[j]: " << p[j] << std::endl;
				if (p[j] > 0 && p[j] < 60) {
					q[j] = static_cast<uchar>(10 * p[j]);
					//std::cout << "p[j]: " << p[j] << std::endl;
				}
			}
		}
	}
	
}