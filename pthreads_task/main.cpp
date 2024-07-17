#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void *detectBorderOnXAxis(void *ptr)
{
    cv::Mat *img = (cv::Mat *)ptr;
    cv::Mat *Rx = (cv::Mat *)malloc(sizeof(cv::Mat));

    // Definição do operador de Prewitt
    cv::Mat Gx = (cv::Mat_<float>(3, 3) << -1, 0, 1,
                  -1, 0, 1,
                  -1, 0, 1);

    // Detectar bordas na horizontal
    cv::filter2D(*img, *Rx, -1, Gx);

    // Limitar os valores até 255
    cv::min(*Rx, 255, *Rx);

    return Rx;
}

void *detectBorderOnYAxis(void *ptr)
{
    cv::Mat *img = (cv::Mat *)ptr;
    cv::Mat *Ry = (cv::Mat *)malloc(sizeof(cv::Mat));

    // Definição do operador de Prewitt
    cv::Mat Gy = (cv::Mat_<float>(3, 3) << -1, -1, -1,
                  0, 0, 0,
                  1, 1, 1);

    // Detectar bordas na vertical
    cv::filter2D(*img, *Ry, -1, Gy);

    // Limitar os valores até 255
    cv::min(*Ry, 255, *Ry);

    return Ry;
}

int main(int argc, char **argv)
{
    cv::Mat *Rx, *Ry;
    pthread_t xThread, yThread;
    int pid, child, status;

    if (argc != 3)
    {
        std::cerr << "Modo de uso: " << argv[0] << " <imagem_de_entrada> <imagem_de_saida>" << std::endl;
        return 1;
    }

    // Ler imagem fornecida
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    // Detectar bordas em threads separadas
    pthread_create(&xThread, NULL, detectBorderOnXAxis, &img);
    pthread_create(&yThread, NULL, detectBorderOnYAxis, &img);

    // Aguardar o término das threads
    pthread_join(xThread, reinterpret_cast<void **>(&Rx));
    pthread_join(yThread, reinterpret_cast<void **>(&Ry));

    // Unir as bordas detectadas
    cv::Mat R = *Rx + *Ry;
    cv::min(R, 255, R); // Limitar os valores até 255

    // Salvar imagem final
    cv::imwrite(argv[2], R);

    // Liberar memória
    free(Rx);
    free(Ry);

    return 0;
}
