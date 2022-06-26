import tkinter as tk
from tkinter.filedialog import askopenfilename, asksaveasfilename
import os
import shutil


def open_Config_Window():

	os.system("notepad config.txt")

#def new_Window():
      
    # Toplevel object which will 
    # be treated as a new window
     #ConfigWindow = tk.Toplevel(window)


    # sets the title of the
    # Toplevel widget
    # ConfigWindow.title("New Window")
  
    # sets the geometry of toplevel
    # ConfigWindow.geometry("700x700")
  
    # A Label widget to show in toplevel
   #  tk.Label(ConfigWindow, 
    #       text ="This is a new ConfigWindow").pack()

def open_file():
    """Open a file for editing."""
    filepath = askopenfilename(
        filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")]
    )
    if not filepath:
        return
    txt_edit.delete(1.0, tk.END)
    with open(filepath, "r") as input_file:
        text = input_file.read()
        txt_edit.insert(tk.END, text)
    window.title(f"Simple Text Editor - {filepath}")

def save_file():
    """Save the current file as a new file."""
    filepath = asksaveasfilename(
        defaultextension="txt",
        filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")],
    )
    if not filepath:
        return
    with open(filepath, "w") as output_file:
        text = txt_edit.get(1.0, tk.END)
        output_file.write(text)
    window.title(f"Simple Text Editor - {filepath}")

def save_file_with_keys():
    """Save the current file as a new file."""
    filepath = asksaveasfilename(
        defaultextension="txt",
        filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")],
    )
    if not filepath:
        return
    with open(filepath, "w") as output_file:
        text = txt_edit2.get(1.0, tk.END)
        output_file.write(text)
    window.title(f"KMC CIPHER - {filepath}")

    """Save the current file as a new file."""
    filepath = asksaveasfilename(
        defaultextension="mkeys",
        filetypes=[("keys files", "*.mkeys"), ("All Files", "*.*")],
    )
    if not filepath:
        return
    with open(filepath, "w") as output_file:
        shutil.copyfile("pass.mkey", filepath)
    window.title(f"KMC CIPHER - {filepath}") 

def Crypter():
   txt_edit2.delete('1.0', "end")
   txt_edit2.delete('1.0', "end")
   txt_edit2.delete('1.0', "end")
   texteAcrypter=txt_edit.get("1.0","end")
   print(texteAcrypter)
   f = open("a.txt", "w")
   f.write(texteAcrypter)
   f.close()
   os.system("KMC.exe")
   u = open("C_Output.txt")
   i = 1
   while i<1000:
     text = u.read()
     txt_edit2.insert("1.0", text)
     i += 1
   u.close()
   print("Showing ", i ,"characters")


window = tk.Tk()
window.title("KMC CIPHER V0.2")
window.rowconfigure(0, minsize=500, weight=1)
window.columnconfigure(1, minsize=1000, weight=1)


txt_edit = tk.Text(window)
txt_edit2 = tk.Text(window)

fr_buttons = tk.Frame(window, relief=tk.RAISED, bd=2)
fr_buttons2 = tk.Frame(window, relief=tk.RAISED, bd=2)

btn_open = tk.Button(fr_buttons, text="Open", command=open_file)
btn_save = tk.Button(fr_buttons, text="Save As...", command=save_file)
btn_open_config = tk.Button(fr_buttons, text="Open Config File", command = open_Config_Window)
btn_crypt = tk.Button(text="Crypter", command = Crypter)

btn_save_crypted = tk.Button(fr_buttons2, text="Save file with keys...", command = save_file_with_keys )

btn_open.grid(row=0, column=0, sticky="ew", padx=5, pady=5)
btn_save.grid(row=1, column=0, sticky="ew", padx=5)
btn_open_config.grid(row=3, column=0, sticky="ew", padx=5, pady=5)
btn_crypt.grid(row=1, column=1, sticky="ew", padx=5, pady=5)

btn_save_crypted.grid(row=0, column=0,sticky="ew", padx=5, pady=5)

fr_buttons.grid(row=0, column=0, sticky="nsew")
fr_buttons2.grid(row=2, column=0, sticky="nsew")
txt_edit.grid(row=0, column=1)
txt_edit2.grid(row=2, column=1)



window.mainloop()

