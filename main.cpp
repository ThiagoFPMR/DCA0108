#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main()
{
    int pid, child, status;
    // cv::Mat Rx, Ry;

    cv::Mat img = cv::imread("coins.png", cv::IMREAD_GRAYSCALE);

    cv::Mat Rx = cv::Mat(img.rows, img.cols, img.type(), mmap(NULL, img.rows * img.cols * img.elemSize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    cv::Mat Ry = cv::Mat(img.rows, img.cols, img.type(), mmap(NULL, img.rows * img.cols * img.elemSize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    // Definição dos operadores de Prewitt
    cv::Mat Gx = (cv::Mat_<float>(3, 3) << -1, 0, 1,
                  -1, 0, 1,
                  -1, 0, 1);

    cv::Mat Gy = (cv::Mat_<float>(3, 3) << -1, -1, -1,
                  0, 0, 0,
                  1, 1, 1);

    // Processo filho de detectção de bordas no eixo x
    pid = fork();
    if (pid == 0)
    {
        cv::filter2D(img, Rx, -1, Gx);
        exit(0);
    }
    child = wait(&status);

    // Processo filho de detectção de bordas no eixo y
    pid = fork();
    if (pid == 0)
    {
        cv::filter2D(img, Ry, -1, Gy);
        exit(0);
    }
    child = wait(&status);

    cv::Mat R = Rx + Ry;
    cv::min(R, 255, R); // Manter os valores até 255

    // Mostrar a imagem final
    cv::imshow("Filtered Image", R);
    cv::waitKey(0);

    // Liberar memória
    munmap(Rx.data, img.rows * img.cols * img.elemSize());
    munmap(Ry.data, img.rows * img.cols * img.elemSize());

    return 0;
}
