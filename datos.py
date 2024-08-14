import pandas as pd

# Datos de ejemplo
horarios = {
    'Grupo': ['7° M', '7° M', '7° M', '7° M', '7° M', '7° M', '7° M'],
    'Materia': [
        'CONMUTADORES Y REDES INALAMBRICAS',
        'DESARROLLO DE APLICACIONES WEB Y MOVILES',
        'INTELIGENCIA ARTIFICIAL',
        'OPT. 1 - SEGURIDAD EN COMPUTO',
        'OPT. 2 - ANALISIS DE VULNERABILIDADES',
        'PRACTICA PROFESIONAL 2',
        'SISTEMAS OPERATIVOS'
    ],
    'Lun': ['1700-1900', '1900-2100', '-', '-', '-', '-', '-'],
    'Mar': ['-', '1700-1900', '1500-1700', '-', '2000-2200', '-', '1900-2000'],
    'Mie': ['1800-1900', '-', '1900-2000', '1700-1800', '-', '-', '1500-1700'],
    'Jue': ['-', '-', '1600-1700', '1800-2000', '1700-1800', '-', '-'],
    'Vie': ['1500-1600', '-', '-', '1600-1700', '1700-1800', '-', '1800-2000'],
    'Sab': ['-', '-', '-', '-', '-', '-', '-'],
    'Dom': ['-', '-', '-', '-', '-', '-', '-'],
    'Profesor': [
        'GUTIERREZ ALFARO LUIS, DR.',
        'RUIZ OVALLE JORGE HUMBERTO, DR',
        'GONZALEZ SCARPULLI DANIEL, DR.',
        'TRECE TRECE COMODIN 13',
        'GUTIERREZ ALFARO LUIS, DR.',
        'TEVERA MANDUJANO JUAN JOSE, DR.',
        'SANDOVAL ZUÑIGA LUIS MANUEL, MTRO.'
    ]
}

# Convertir a DataFrame
df_horarios = pd.DataFrame(horarios)
