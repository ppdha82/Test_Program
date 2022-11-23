import cv2
import numpy as np
import sys

if len(sys.argv) < 3:
    print("few argment(", len(sys.argv), ")")
    sys.exit()
'''
class VideoCaptureYUV:
    def __init__(self, filename, size):
        self.height, self.width = size
        self.frame_len = (int)(self.width * self.height * 3 / 2)
        self.f = open(filename, 'rb')
        self.shape = (int(self.height * 1.5), self.width)

    def read_raw(self):
        try:
            raw = self.f.read(self.frame_len)
            yuv = np.frombuffer(raw, dtype=np.uint8)
            yuv = yuv.reshape(self.shape)
        except Exception as e:
            print(str(e))
            return False, None
        return True, yuv

    def read(self):
        ret, yuv = self.read_raw()
        if not ret:
            return ret, yuv
        bgr = cv2.cvtColor(yuv, cv2.COLOR_YUV2BGR_NV12)
        return ret, bgr

if __name__ == "__main__":
    filename = "test.mp4"
    size = (720, 1280)
    cap = VideoCaptureYUV(filename, size)

    while 1:
        ret, frame = cap.read()
        if ret:
            cv2.imshow("frame", frame)
            cv2.waitKey(0)
        else:
            break
'''
cap = cv2.VideoCapture(sys.argv[1])

print("argv[2] = ", sys.argv[2])

while(cap.isOpened()):
    ret, frame = cap.read()
    if ret == False:
        print("Finish cap read")
        break
    if sys.argv[2] == "1":
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('frame', gray)
    elif sys.argv[2] == "2":
        rgb = cv2.cvtColor(frame, cv2.COLOR_YUV2BGR)
        cv2.imshow('frame', rgb)
    elif sys.argv[2] == "3":
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2BGRA)
        cv2.imshow('frame', rgb)

    if cv2.waitKey(1) & 0xff == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

