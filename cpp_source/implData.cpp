/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2024년 11월 19일 19시 15분 58초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@gmail.com
 *        Company:  No co-operation
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    // 입력 파일과 출력 파일 이름
    std::string inputFilename = "MotionFile_Slave_A.txt";
    std::string outputFilename = "MotionFile_Slave_A.txt_export";

    // 파일 스트림 열기
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << inputFilename << std::endl;
        return 1;
    }

    std::string line;
    // 각 줄을 처리
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> values;
        std::string value;

        // 데이터를 빈칸이나 탭을 기준으로 분리
        while (iss >> value) {
            values.push_back(value);
        }

        // 두 번째부터 네 번째 열을 0으로 변경 (1, 2, 3 번째 인덱스)
        if (values.size() >= 4) {
            values[1] = "0";
            values[2] = "0";
            values[3] = "0";
        }

        // 결과를 출력 파일에 쓰기
        for (size_t i = 0; i < values.size(); ++i) {
            outputFile << values[i];
            if (i < values.size() - 1) {
                outputFile << " "; // 빈칸 구분자
            }
        }
        outputFile << "\n"; // 줄 바꿈
    }

    inputFile.close();
    outputFile.close();

    std::cout << "데이터가 성공적으로 수정되어 " << outputFilename << " 파일에 저장되었습니다." << std::endl;
    return 0;
}
