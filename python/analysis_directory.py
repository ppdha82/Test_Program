import os
import pandas as pd
from datetime import datetime

def get_directory_structure (root_path):
    file_list = []

    for root, dirs, files in os.walk (root_path):
        for file in files:
            file_path = os.path.join (root, file)

            relative_path = os.path.relpath(root, root_path)
            if relative_path == ".":
                relative_path = "Root"

            try:
                stats = os.stat (file_path)
                file_info = {
                    "상위 폴더": relative_path,
                    "파일명": file,
                    "확장자": os.path.splitext (file)[1].lower(),
                    "파일 크기(KB)": round (stats.st_size / 1024, 2),
                    "최종 수정일": datetime.fromtimestamp (stats.st_mtime).strftime('%Y-%m-%d %H:%M:%S'),
                    "전체 경로": file_path
                }
                file_list.append (file_info)
            except Exception as e:
                print(f"오류 발생 ({file_path}): {e}")

    return file_list

def save_to_excel (data, output_name):
    df = pd.DataFrame(data)
    df.to_excel (output_name, index = False, engine = 'openpyxl')
    print (f"성공: 결과물이 '{output_name}'로 저장되었습니다.")

if __name__ == "__main__":
    target_directory = input ("탐색할 폴더 경로를 입력하세요: ").strip()

    if os.path.exists (target_directory):
        print(f"'{target_directory}' 분석 중...")
        structure_data = get_directory_structure (target_directory)

        output_filename = f"folder_structre_{datetime.now().strftime('%Y%m%d_%H%M%S')}.xlsx"
        save_to_excel (structure_data, output_filename)
    else:
        print("입력하신 경로가 존재하지 않습니다.")
