import tkinter as tk
from tkinter import messagebox

# Function for Submit button
def submit_form():
    name = entry_name.get()
    email = entry_email.get()
    gender = gender_var.get()
    course = course_var.get()
    password = entry_password.get()

    if name and email and gender and course != "Select Course" and password:
        messagebox.showinfo("Registration Successful",
                            f"Name: {name}\nEmail: {email}\nGender: {gender}\nCourse: {course}")
    else:
        messagebox.showwarning("Error", "Please fill all fields correctly!")

# Create main window
root = tk.Tk()
root.title("Registration Form")
root.geometry("400x400")
root.configure(bg="#f0f0f0")

# Heading
tk.Label(root, text="Student Registration Form", font=("Arial", 16, "bold"), bg="#f0f0f0").pack(pady=10)

# Name
tk.Label(root, text="Full Name:", font=("Arial", 12), bg="#f0f0f0").pack()
entry_name = tk.Entry(root, width=30)
entry_name.pack(pady=5)

# Email
tk.Label(root, text="Email:", font=("Arial", 12), bg="#f0f0f0").pack()
entry_email = tk.Entry(root, width=30)
entry_email.pack(pady=5)

# Gender
tk.Label(root, text="Gender:", font=("Arial", 12), bg="#f0f0f0").pack()
gender_var = tk.StringVar(value="None")
tk.Radiobutton(root, text="Male", variable=gender_var, value="Male", bg="#f0f0f0").pack()
tk.Radiobutton(root, text="Female", variable=gender_var, value="Female", bg="#f0f0f0").pack()

# Course Dropdown
tk.Label(root, text="Course:", font=("Arial", 12), bg="#f0f0f0").pack()
course_var = tk.StringVar(value="Select Course")
courses = ["B.Tech", "B.Sc", "B.Com", "MCA", "MBA"]
tk.OptionMenu(root, course_var, *courses).pack(pady=5)

# Password
tk.Label(root, text="Password:", font=("Arial", 12), bg="#f0f0f0").pack()
entry_password = tk.Entry(root, width=30, show="*")
entry_password.pack(pady=5)

# Buttons
tk.Button(root, text="Submit", command=submit_form, bg="green", fg="white", width=10).pack(pady=10)
tk.Button(root, text="Exit", command=root.quit, bg="red", fg="white", width=10).pack()

# Run Application
root.mainloop()
