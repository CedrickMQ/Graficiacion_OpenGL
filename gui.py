import tkinter as tk
from tkinter import ttk
from generador_horarios import df_horarios_generados

class HorariosApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Generador de Horarios Académicos")
        
        self.tree = ttk.Treeview(root, columns=("Grupo", "Materia", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom", "Profesor"), show='headings')
        self.tree.heading("Grupo", text="Grupo")
        self.tree.heading("Materia", text="Materia")
        self.tree.heading("Lun", text="Lun")
        self.tree.heading("Mar", text="Mar")
        self.tree.heading("Mie", text="Mie")
        self.tree.heading("Jue", text="Jue")
        self.tree.heading("Vie", text="Vie")
        self.tree.heading("Sab", text="Sab")
        self.tree.heading("Dom", text="Dom")
        self.tree.heading("Profesor", text="Profesor")
        self.tree.pack(expand=True, fill='both')

        self.cargar_datos(df_horarios_generados)

    def cargar_datos(self, df):
        for index, row in df.iterrows():
            self.tree.insert('', tk.END, values=tuple(row))

if __name__ == "__main__":
    root = tk.Tk()
    app = HorariosApp(root)
    root.mainloop()
