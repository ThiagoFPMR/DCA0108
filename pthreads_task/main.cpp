#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void *detectBorderOnXAxis(void *img)
{
    cv::Mat *img = (cv::Mat *)img;
    cv::Mat *Rx = (cv::Mat *)malloc(sizeof(cv::Mat));

    // Definição do operador de Prewitt
    cv::Mat Gx = (cv::Mat_<float>(3, 3) << -1, 0, 1,
                  -1, 0, 1,
                  -1, 0, 1);

    cv::filter2D(*img, Rx, -1, Gx);

    return Rx;
}

void *detectBorderOnYAxis(void *img)
{
    cv::Mat *img = (cv::Mat *)img;
    cv::Mat *Ry = (cv::Mat *)malloc(sizeof(cv::Mat));

    // Definição do operador de Prewitt
    cv::Mat Gy = (cv::Mat_<float>(3, 3) << -1, -1, -1,
                  0, 0, 0,
                  1, 1, 1);

    cv::filter2D(*img, Ry, -1, Gy);

    return Ry;
}

int main(int argc, char **argv)
{
    cv::Mat *Rx, *Ry;
    pthread_t xThread, yThread;
    int pid, child, status;

    if (argc != 3)
    {
        std::cerr << "Modo de uso: " << argv[0] << " <input_image> <output_image>" << std::endl;
        return 1;
    }

    // Ler imagem fornecida
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    pthread_create(&xThread, NULL, detectBorderOnXAxis, &img);
    pthread_create(&yThread, NULL, detectBorderOnYAxis, &img);

    pthread_join(xThread, (void *)&Rx);
    pthread_join(yThread, (void *)&Ry);

    cv::Mat R = *Rx + *Ry;
    cv::min(R, 255, R); // Limitar os valores até 255

    // Salvar imagem final
    cv::imwrite(argv[2], R);

    // Liberar memória
    free(Rx);
    free(Ry);

    return 0;
}
