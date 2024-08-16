# main.py
from datos import df_profesores, df_clases
from generador_horarios import asignar_profesores
from voz import hablar, configurar_voz

# Configurar la voz
configurar_voz(velocidad=150, volumen=0.9, voz_masculina=True)

# Realizar asignaciones
asignaciones = asignar_profesores(df_profesores, df_clases)

# Anunciar las asignaciones
for asignacion in asignaciones:
    mensaje = f"El profesor {asignacion['Profesor']} ha sido asignado a la clase {asignacion['Clase']} en el horario {asignacion['Horario']}."
    print(mensaje)  # También lo mostramos en la consola
    hablar(mensaje)  # Lo decimos en voz alta
