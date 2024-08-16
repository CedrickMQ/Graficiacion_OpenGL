import pyttsx3

# Configurar el motor de voz
engine = pyttsx3.init()

def configurar_voz(velocidad=150, volumen=0.9, voz_masculina=False):
    # Ajustar velocidad
    engine.setProperty('rate', velocidad)
    # Ajustar volumen
    engine.setProperty('volume', volumen)
    # Seleccionar voz femenina en español
    voices = engine.getProperty('voices')
    for voice in voices:
        if "spanish" in voice.languages or "es" in voice.id:
            engine.setProperty('voice', voice.id)
            break

def hablar(texto):
    engine.say(texto)
    engine.runAndWait()

# Configuración de voz inicial
configurar_voz(velocidad=150, volumen=0.9, voz_masculina=False)
