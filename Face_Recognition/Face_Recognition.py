import face_recognition
import cv2
import numpy as np
import csv
import os
from datetime import datetime
import winsound


# Set paths for Employee and Client photos, and attendance records
os.chdir(os.path.dirname(os.path.realpath(__file__)))
Employee_photos_path = "./Employee/Photos/"
Client_photos_path = "./Client/Photos/"
Employee_attendance_csv = "./Employee/Employee_Attendance.csv"
Registered_Client_csv = "./Client/Registered_Clients.csv"

# Open CSV files to write attendance records and registered client
f_Employee = open(Employee_attendance_csv, "a", newline="")
lnwriter_Employee = csv.writer(f_Employee)

f_Client = open(Registered_Client_csv, "a", newline="")
lnwriter_Client = csv.writer(f_Client)

# If CSV files are empty, write headers
if os.path.getsize(Employee_attendance_csv) == 0:
    lnwriter_Employee.writerow(["Name", "Time", "Date"])
    
if os.path.getsize(Registered_Client_csv) == 0:
    lnwriter_Client.writerow(["Name", "Email", "Password", "Time", "Date"])

# Load known faces and their encodings from photos
known_faces_encodings = []
known_faces_names = []
known_faces_type = []
known_faces_email = []
known_faces_password = []

for file in os.listdir(Employee_photos_path):
    image = face_recognition.load_image_file(os.path.join(Employee_photos_path, file))
    encoding = face_recognition.face_encodings(image)[0]
    known_faces_encodings.append(encoding)
    known_faces_names.append(os.path.splitext(file)[0])
    known_faces_type.append("Employee")
    known_faces_email.append("")
    known_faces_password.append("")

for file in os.listdir(Client_photos_path):
    image = face_recognition.load_image_file(os.path.join(Client_photos_path, file))
    encoding = face_recognition.face_encodings(image)[0]
    known_faces_encodings.append(encoding)
    known_faces_names.append(os.path.splitext(file)[0])
    known_faces_type.append("Client")
    known_faces_email.append("")
    known_faces_password.append("")

# Initialize variables for face detection and recognition
face_locations = []
face_encodings = []

frame_count = 0
process_every_n_frames = 60

last_recognition_time = {}

# Set up video capture
video_capture = cv2.VideoCapture(0)

# Main loop for face detection and recognition
while True:
    _, frame = video_capture.read()
    frame = cv2.flip(frame, 1)
    frame_count += 1
    
    # Only process every n frames to save processing power
    if frame_count % process_every_n_frames == 0:
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        face_locations = face_recognition.face_locations(rgb_frame)
        face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

        # Compare face encodings against known faces
        for face_encoding in face_encodings:
            matches = face_recognition.compare_faces(known_faces_encodings, face_encoding)
            name = ""
            best_match_index = 0
            face_distance = face_recognition.face_distance(known_faces_encodings, face_encoding)
            if len(face_distance) > 0:
                best_match_index = np.argmin(face_distance)
                if matches[best_match_index]:
                    name = known_faces_names[best_match_index]

            # Check if face has been recognized recently to avoid duplicate entries
            if name in last_recognition_time:
                time_since_recognition = (datetime.now() - last_recognition_time[name]).seconds
                if time_since_recognition < 10:
                    continue

            # Record attendance or register new Employee/Client
            if name in known_faces_names:
                if known_faces_type[best_match_index] == "Employee":
                    print("Employee member recognized:", name)
                    winsound.PlaySound("./Employee/Old.wav", winsound.SND_FILENAME)
                    current_time = datetime.now().strftime("%H:%M:%S")
                    current_date = datetime.now().strftime("%Y-%m-%d")
                    lnwriter_Employee.writerow([name, current_time, current_date])
                else:
                    print("Client recognized:", name)
                    winsound.PlaySound("./Client/Old.wav", winsound.SND_FILENAME)
                    with open(Registered_Client_csv, "r") as f:
                        reader = csv.reader(f)
                        email, password = "", ""
                        for row in reader:
                            if row[0] == name:
                                email, password, *_ = row[1:]
                                break
                        if email != "":
                            current_time = datetime.now().strftime("%H:%M:%S")
                            current_date = datetime.now().strftime("%Y-%m-%d")
                            lnwriter_Client.writerow([name, email, password, current_time, current_date])
                            print("Email:", email)
                            print("Password:", password)
                            known_faces_email[best_match_index] = email
                            known_faces_password[best_match_index] = password
                        else:
                            if known_faces_email[best_match_index] == "" and known_faces_password[best_match_index] == "":
                                cv2.destroyAllWindows()
                                email = input("Please enter your email: ")
                                password = input("Please enter a password: ")
                                current_time = datetime.now().strftime("%H:%M:%S")
                                current_date = datetime.now().strftime("%Y-%m-%d")
                                lnwriter_Client.writerow([name, email, password, current_time, current_date])
                                print("Email and Password updated.")
                                known_faces_email[best_match_index] = email
                                known_faces_password[best_match_index] = password
                            else:
                                print("Email and Password already exist.")
                    last_recognition_time[name] = datetime.now()

            else:
                # If face is unrecognized, prompt user to register as Employee or Client
                cv2.destroyAllWindows()
                type_choice = input("\n1. Employee\n2. Client\n3. Cancel\nAre you a new Employee or a new Client?: ")
                if type_choice == "1":
                    password = input("Please enter the Employee password: ")
                    if password == "12345678":
                        name = input("Please enter your name: ")
                        Employee_photos_path = "./Employee/Photos/"
                        cv2.imwrite(f"{Employee_photos_path}/{name}.jpg", frame)
                        new_img = face_recognition.load_image_file(f"{Employee_photos_path}/{name}.jpg")
                        new_encoding = face_recognition.face_encodings(new_img)[0]
                        known_faces_encodings.append(new_encoding)
                        known_faces_names.append(name)
                        known_faces_type.append("Employee")
                        known_faces_email.append("")
                        known_faces_password.append("")
                        current_time = datetime.now().strftime("%H:%M:%S")
                        current_date = datetime.now().strftime("%Y-%m-%d")
                        lnwriter_Employee.writerow([name, current_time,current_date])
                        print("New Employee member added:", name)
                        winsound.PlaySound("./Employee/New.wav", winsound.SND_FILENAME)
                    else:
                        print("Incorrect password, please try again.")
                elif type_choice == "2":
                    name = input("Please enter your name: ")
                    email = ""
                    password = ""
                    for i in range(len(known_faces_names)):
                        if known_faces_names[i] == name:
                            email = known_faces_email[i]
                            password = known_faces_password[i]
                            break
                    if email != "" and password != "":
                        Client_photos_path = "./Client/Photos/"
                        cv2.imwrite(f"{Client_photos_path}/{name}.jpg", frame)
                        new_img = face_recognition.load_image_file(f"{Client_photos_path}/{name}.jpg")
                        new_encoding = face_recognition.face_encodings(new_img)[0]
                        known_faces_encodings.append(new_encoding)
                        known_faces_names.append(name)
                        known_faces_type.append("Client")
                        known_faces_email.append(email)
                        known_faces_password.append(password)
                        current_time = datetime.now().strftime("%H:%M:%S")
                        current_date = datetime.now().strftime("%Y-%m-%d")
                        lnwriter_Client.writerow([name, email, password, current_time, current_date])
                        print("New Client added:", name)
                        winsound.PlaySound("./Client/New.wav", winsound.SND_FILENAME)
                    else:
                        if email == "" and password == "":
                            email = input("Please enter your email: ")
                            password = input("Please enter a password: ")
                            Client_photos_path = "./Client/Photos/"
                            cv2.imwrite(f"{Client_photos_path}/{name}.jpg", frame)
                            new_img = face_recognition.load_image_file(f"{Client_photos_path}/{name}.jpg")
                            new_encoding = face_recognition.face_encodings(new_img)[0]
                            known_faces_encodings.append(new_encoding)
                            known_faces_names.append(name)
                            known_faces_type.append("Client")
                            known_faces_email.append(email)
                            known_faces_password.append(password)
                            current_time = datetime.now().strftime("%H:%M:%S")
                            current_date = datetime.now().strftime("%Y-%m-%d")
                            lnwriter_Client.writerow([name, email, password, current_time, current_date])
                            print("New Client added:", name)
                            winsound.PlaySound("./Client/New.wav", winsound.SND_FILENAME)
                        else:
                            print("Email and Password already exist.")

        # Flush CSV files to save
        f_Employee.flush()
        f_Client.flush()
        # Loop through recognized faces to check time since last recognition
        for name in last_recognition_time.keys():
            time_since_recognition = (datetime.now() - last_recognition_time[name]).seconds
            # Remove name from dictionary if not recognized in last 60 seconds
            if time_since_recognition >= 60:
                last_recognition_time.pop(name)

    # Show video feed with recognized faces
    cv2.imshow("Office System", frame)
    cv2.setWindowProperty("Office System", cv2.WND_PROP_TOPMOST, 1)
    # Exit program if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release video capture and close CSV files
video_capture.release()
cv2.destroyAllWindows()
f_Employee.close()
f_Client.close()