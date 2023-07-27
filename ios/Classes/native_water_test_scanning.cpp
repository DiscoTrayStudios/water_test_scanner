#include "native_water_test_scanning.hpp"
#include "water_test_scanner.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>

struct ColorOutput createColorOutput(cv::Scalar color, int idx, double value)
{
    struct ColorOutput coloroutput;
    coloroutput.blue = static_cast<int32_t>(color[0]);
    coloroutput.green = static_cast<int32_t>(color[1]);
    coloroutput.red = static_cast<int32_t>(color[2]);
    coloroutput.idx = static_cast<int32_t>(idx);
    coloroutput.value = value;
    return coloroutput;
}

extern "C"
struct DetectionResult *create_detection_result(vector<ColorOutput> array, int exit_code)
{
    struct DetectionResult *detectionResult = (struct DetectionResult *)malloc(sizeof(struct DetectionResult));
    detectionResult->color1 = &array[0];
    detectionResult->color2 = &array[1];
    detectionResult->color3 = &array[2];
    detectionResult->color4 = &array[3];
    detectionResult->color5 = &array[4];
    detectionResult->color6 = &array[5];
    detectionResult->color7 = &array[6];
    detectionResult->color8 = &array[7];
    detectionResult->color9 = &array[8];
    detectionResult->color10 = &array[9];
    detectionResult->color11 = &array[10];
    detectionResult->color12 = &array[11];
    detectionResult->color13 = &array[12];
    detectionResult->color14 = &array[13];
    detectionResult->color15 = &array[14];
    detectionResult->color16 = &array[15];
    detectionResult->exitCode = exit_code;
    return detectionResult;
}


struct DetectionResult *native_detect_colors(char *str)
{
    cv::Mat mat = cv::imread(str);

    if (mat.size().width == 0 || mat.size().height == 0) {

        vector<ColorOutput> out(16);

        for (int i = 0; i < 16; i++) {
            out[i] = createColorOutput(cv::Scalar(), i, 0);
        }

        return create_detection_result(out, 2);
    }

    vector<ColorOutput> colors(16);
    Result out = TestScanner::detect_colors(mat, colors);

    cv::imwrite(str, out.image);

    return out.result;
}