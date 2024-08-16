import pandas as pd
from datos import df_horarios

def generar_horarios(df):
    # Implementar la lógica para evitar solapamientos
    horarios_generados = []
    
    # Aquí se añadiría la lógica para evitar solapamientos y manejar la disponibilidad de los profesores
    # Por ejemplo, podríamos filtrar las clases según la disponibilidad de los profesores y comprobar conflictos
    
    for i, row in df.iterrows():
        # Comprobar y añadir lógica para gestionar solapamientos y restricciones
        horarios_generados.append(row)
    
    return pd.DataFrame(horarios_generados)

# Generar los horarios
df_horarios_generados = generar_horarios(df_horarios)
