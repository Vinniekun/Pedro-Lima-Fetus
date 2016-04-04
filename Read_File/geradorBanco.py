import sqlite3
import os

if ('cartas.db' in os.listdir()):
    os.system("mv cartas.db cartas.db.old")

conn = sqlite3.connect('cartas.db')
cursor = conn.cursor()
cursor.execute("""
CREATE TABLE cartas (
        id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        nome_carta VARCHAR(80) NOT NULL,
        tipo_carta VARCHAR(80) NOT NULL,
        card_color VARCHAR(10) NOT NULL,
        primary_cost INTEGER NOT NULL,
        secondary_cost INTEGER,
        armor INTEGER,
        carga INTEGER,
        lifetime INTEGER,
        power INTEGER,
        texto TEXT NOT NULL
);
""")

class Card:
    def __init__(self):
        self.dic = {}

    def set(self, attr,value):
        if value != "":
            self.dic[attr] = value

    def sql(self):
        keys = list(self.dic.keys())
        keys.sort()
        stmt = "INSERT INTO cartas (" + ", ".join(keys) + ") VALUES ("
        values = []
        for key in keys:
            values.append("'"+ str(self.dic[key]) +"'")
        return stmt + ", ".join(values) + ")"


cartas = []
carta = Card()
#for cor in ("blue.txt", "red.txt", "yellow.txt"):
#    with open(cor) as txt:
with open("deck") as txt:
    while txt.readline()[:-1] != "card:":
        pass
    while True:
        linha = txt.readline()[:-1]
        if "version control:" in linha:
            # terminou de ler
            cartas.append(carta)
            carta = Card()
            break
        elif linha.replace("\t","").split(":")[0] in ("has styling", "notes","time created","time modified", "bg color", "image","edition"):
            # ignora
            continue
        elif "card:" in linha:
            # nova carta
            cartas.append(carta)
            carta = Card()
            continue
        elif "text:" in linha:
            # bloco de texto
            try:
                text = [linha.split(": ")[1]]
            except:
                text = []
            while True:
                linha = txt.readline()[:-1]
                if "card color:" in linha:
                    # fim do bloco de texto
                    carta.set("texto","\n".join(text))
                    break
                text.append(linha.replace("\t",""))
        # salva atributo
        attr,value = linha.replace("\t","").split(": ")
        carta.set(attr.replace(" ","_"),value)

for c in cartas:
    cursor.execute(c.sql())
conn.commit()

conn.close()
