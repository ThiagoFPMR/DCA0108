#include <opencv2/opencv.hpp>

int main() {
    // Create a VideoCapture object to access the webcam
    cv::VideoCapture cap(0); // 0 means the first connected webcam

    // Check if the webcam is opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the webcam." << std::endl;
        return -1;
    }

    // Create a window to display the video feed
    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

    while (true) {
        cv::Mat frame;
        
        // Capture a new frame from the webcam
        cap >> frame;

        // Check if the frame is empty (this can happen if there's a problem with the webcam)
        if (frame.empty()) {
            std::cerr << "Error: Could not capture a frame." << std::endl;
            break;
        }

        // Display the frame in the created window
        cv::imshow("Webcam", frame);

        // Wait for 30 ms and break the loop if the user presses the 'q' key
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Release the VideoCapture object
    cap.release();

    // Destroy all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
