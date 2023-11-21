import tkinter as tk
import mysql.connector as mysql
import time
from tkinter import messagebox
from tkinter.simpledialog import askinteger, askstring
from PIL import Image, ImageTk
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas as pdf_canvas


# Fonction de connexion à la base de données
def se_connecter():
    global con
    try: 
        # Afficher un message "Connect en cours"
        message_label.config(text="Connect en cours...")
        fenetre.update()

        con = mysql.connect(
            user='root',
            passwd='',
            host='localhost',
            port=3306,
            database='gestion_stock'
        )
        if con.is_connected():
            # Attendre pendant 1 seconde (à des fins de démonstration)
            time.sleep(5)

            # Activer à nouveau le bouton de connexion
            bouton_connexion.config(state=tk.NORMAL)

            # Afficher le message "Connecté à la base de données MySQL !"
            message_label.config(text="Connecté à la base de données MySQL !")

             # Créer une nouvelle fenêtrea
            autre_fenetre = tk.Toplevel(fenetre)
            autre_fenetre.title("BASE DE DONNEES STOCK")
            autre_fenetre.geometry("500x500")
            autre_fenetre.resizable(height=False, width=False)
            autre_fenetre.configure(bg="slategray2")


        

            # Fonction pour récupérer les noms des tables
            def obtenir_tables():
                try:
                    cursor = con.cursor()
                    cursor.execute("SHOW FULL TABLES WHERE TABLE_TYPE = 'BASE TABLE'")
                    tables = [table[0] for table in cursor.fetchall()]
                    cursor.close()

                    # Afficher les noms des tables dans une liste déroulante
                    table_listbox.delete(0, tk.END)  # Effacer le contenu précédent
                    table_listbox.configure(background="#F0F0F8") 
                    for table in tables:
                        table_listbox.insert(tk.END, table)




                except mysql.Error as e:
                    message_label_tables.config(text=f"Erreur lors de la récupération des tables : {e}")

            # Fonction pour créer une nouvelle table
            def creer_table():
                    
                    table_name = askstring("Nom du table", "Entrez le Nom du table :")

                    if table_name:
                        num_fields = askinteger("Nombre de champs", "Entrez le nombre de champs :")

                        if num_fields:
                            field_names = []
                            for i in range(num_fields):
                                field_name = askstring(f"Champ {i+1}", f"Entrez le nom du champ {i+1} :")
                                if field_name:
                                    field_type = askstring(f"Type du champ {i+1}", f"Entrez le type du champ {i+1} :")
                                    if field_type:
                                        field_names.append((field_name, field_type))

                            if field_names:
                                try:
                                    cursor = con.cursor()
                                    sql_query = f"CREATE TABLE {table_name} (id INT PRIMARY KEY AUTO_INCREMENT, "

                                    for field_name, field_type in field_names:
                                        sql_query += f"{field_name} {field_type}, "

                                    sql_query = sql_query.rstrip(", ")
                                    sql_query += ")"

                                    cursor.execute(sql_query)
                                    con.commit()
                                    cursor.close()
                                    messagebox.showinfo("Nouvelle table", f"La table {table_name} a été créée avec succès !")

                                    # Mettre à jour la liste des tables
                                    obtenir_tables()

                                except mysql.Error as e:
                                    messagebox.showerror("Erreur", f"Erreur lors de la création de la table : {e}")
                            else:
                                messagebox.showwarning("Aucun champ saisi", "Veuillez saisir au moins un champ.")

                        else:
                            messagebox.showwarning("Nombre de champs non saisi", "Veuillez saisir le nombre de champs.")
                    else:
                        messagebox.showwarning("Nom de table vide", "Veuillez entrer un nom pour la nouvelle table.")


            # Fonction pour supprimer une table
            def supprimer_table():
                # Obtenir le nom de la table sélectionnée dans la liste déroulante
                selected_table = table_listbox.get(tk.ACTIVE)

                if selected_table:
                    if messagebox.askyesno("Confirmation", f"Êtes-vous sûr de vouloir supprimer la table {selected_table} ?"):
                        try:
                            cursor = con.cursor()
                            cursor.execute(f"DROP TABLE {selected_table}")
                            con.commit()
                            cursor.close()
                            messagebox.showinfo("Supprimer table", f"La table {selected_table} a été supprimée avec succès !")

                            # Mettre à jour la liste des tables
                            obtenir_tables()

                        except mysql.Error as e:
                            messagebox.showerror("Erreur", f"Erreur lors de la suppression de la table : {e}")
                else:
                    messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table à supprimer.")

            # Fonction pour modifier une table
            def modifier_table():
                # Obtenir le nom de la table sélectionnée dans la liste déroulante
                selected_table = table_listbox.get(tk.ACTIVE)

                if selected_table:
                    # Créer une nouvelle fenêtre pour modifier les champs de la table
                    champ_fenetre = tk.Toplevel(autre_fenetre)
                    champ_fenetre.title("Modifier les champs de la table")
                    champ_fenetre.geometry("400x400")
                    champ_fenetre.configure(bg="slategray2")

                    # Fonction pour ajouter un champ
                    def ajouter_champ():
                        champ_nom = askstring("Ajouter un champ", "Entrez le nom du champ :")
                        if champ_nom:
                            champ_type = askstring("Ajouter un champ", "Entrez le type du champ (ex: VARCHAR(255)) :")
                            if champ_type:
                                # Ajouter le champ à la table avec le type spécifié
                                try:
                                    cursor = con.cursor()
                                    cursor.execute(f"ALTER TABLE {selected_table} ADD COLUMN {champ_nom} {champ_type}")
                                    con.commit()
                                    cursor.close()
                                    messagebox.showinfo("Ajouter un champ", f"Le champ a été ajouté avec succès : {champ_nom}")

                                    # Mettre à jour les champs affichés
                                    afficher_champs()

                                except mysql.Error as e:
                                    messagebox.showerror("Erreur", f"Erreur lors de l'ajout du champ : {e}")
                            else:
                                messagebox.showwarning("Type de champ non saisi", "Veuillez saisir le type du champ.")
                        else:
                            messagebox.showwarning("Nom de champ vide", "Veuillez entrer un nom pour le champ.")
                    # Fonction pour modifier le nom et le type d'un champ
                    def modifier_champ():
                        selected_champ = champ_listbox.get(tk.ACTIVE)
                        if selected_champ:
                            champ_nom = askstring("Modifier un champ", "Entrez le nouveau nom du champ :")
                            if champ_nom:
                                champ_type = askstring("Modifier un champ", "Entrez le nouveau type du champ (ex: VARCHAR(255)) :")
                                if champ_type:
                                    try:
                                        cursor = con.cursor()
                                        cursor.execute(f"ALTER TABLE {selected_table} CHANGE {selected_champ} {champ_nom} {champ_type}")
                                        con.commit()
                                        cursor.close()
                                        messagebox.showinfo("Modifier un champ", f"Le champ a été modifié avec succès : {selected_champ}")

                                        # Mettre à jour les champs affichés
                                        afficher_champs()

                                    except mysql.Error as e:
                                        messagebox.showerror("Erreur", f"Erreur lors de la modification du champ : {e}")
                                else:
                                    messagebox.showwarning("Type de champ non saisi", "Veuillez saisir le nouveau type du champ.")
                            else:
                                messagebox.showwarning("Nom de champ vide", "Veuillez entrer le nouveau nom du champ.")
                        else:
                            messagebox.showwarning("Aucun champ sélectionné", "Veuillez sélectionner un champ à modifier.")
                    # Fonction pour supprimer un champ
                    def supprimer_champ():
                        selected_champ = champ_listbox.get(tk.ACTIVE)
                        if selected_champ:
                            # Supprimer le champ de la table
                            try:
                                cursor = con.cursor()
                                cursor.execute(f"ALTER TABLE {selected_table} DROP COLUMN {selected_champ}")
                                con.commit()
                                cursor.close()
                                messagebox.showinfo("Supprimer un champ", f"Le champ a été supprimé avec succès : {selected_champ}")

                                # Mettre à jour les champs affichés
                                afficher_champs()

                            except mysql.Error as e:
                                messagebox.showerror("Erreur", f"Erreur lors de la suppression du champ : {e}")

                    # Fonction pour afficher les champs de la table sélectionnée
                    def afficher_champs():
                        try:
                            cursor = con.cursor()
                            cursor.execute(f"SHOW COLUMNS FROM {selected_table}")
                            champs = [champ[0] for champ in cursor.fetchall()]
                            cursor.close()

                            # Afficher les champs dans une liste déroulante
                            champ_listbox.delete(0, tk.END)  # Effacer le contenu précédent
                            for champ in champs:
                                champ_listbox.insert(tk.END, champ)

                        except mysql.Error as e:
                            messagebox.showerror("Erreur", f"Erreur lors de la récupération des champs : {e}")
                


                    # Bouton pour ajouter un champ
                    ajouter_champ_button = tk.Button(champ_fenetre, text="Ajouter un champ", command=ajouter_champ,font=("Arial", 12), bg="#F0F0F8", relief="solid", borderwidth=1)
                    ajouter_champ_button.pack(pady=10)
                    
                    # Bouton pour modifier un champ
                    modifier_champ_button = tk.Button(champ_fenetre, text="Modifier un champ", command=modifier_champ,font=("Arial", 12), bg="#F0F0F8", relief="solid", borderwidth=1)
                    modifier_champ_button.pack(pady=10)

                    # Bouton pour supprimer un champ
                    supprimer_champ_button = tk.Button(champ_fenetre, text="Supprimer un champ", command=supprimer_champ,font=("Arial", 12), bg="#F0F0F8", relief="solid", borderwidth=1)
                    supprimer_champ_button.pack(pady=10)

                    # Liste déroulante pour afficher les champs
                    champ_listbox = tk.Listbox(champ_fenetre, width=50, relief="solid", borderwidth=2)
                    champ_listbox.pack()

                    # Afficher les champs initiaux
                    afficher_champs()

                else:
                    messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table à modifier.")



            def generate_invoice_livrasion_pdf(data):
           
                # Create a PDF canvas
                c = pdf_canvas.Canvas("factures livraison.pdf", pagesize=letter)

                # Set the font size and position for the title
                c.setFont("Helvetica", 20)
                c.drawString(50, 750, "Facture de Livraison")

                # Set the font size and position for the content
                c.setFont("Helvetica", 12)
                y = 700

                # Add content to the document using the provided data
                for row in data:
                    id_livraison = row[0]
                    combien_de_fois_livrer = row[1]
                    benefices = row[2]

                    c.drawString(100, y, "Id Livraison: {}".format(id_livraison))
                    c.drawString(100, y - 20, "Combien de fois livrer: {}".format(combien_de_fois_livrer))
                    c.drawString(100, y - 40, "Bénéfices: {}".format(benefices))
                    # Add more content as needed

                    y -= 60  # Adjust the position for the next content

                    # Add space after the separator
                    y -= 10

                    # Add a separator between each set of data
                    c.line(50, y, 550, y)

                    y -= 20  # Adjust the position for the next content

                # Save the PDF document
                c.save()

            def generate_invoice_produit_pdf(data):
           
                # Create a PDF canvas
                c = pdf_canvas.Canvas("factures Produits.pdf", pagesize=letter)

                # Set the font size and position for the title
                c.setFont("Helvetica", 20)
                c.drawString(50, 750, "Facture de Produit")

                # Set the font size and position for the content
                c.setFont("Helvetica", 12)
                y = 700

                # Add content to the document using the provided data
                for row in data:
                    Id_Article = row[0]
                    nom = row[1]
                    quantite = row[2]
                    bénéfices = row[3]

                    c.drawString(100, y, "Id_Article: {}".format(Id_Article))
                    c.drawString(100, y - 20, "nom: {}".format(nom))
                    c.drawString(100, y - 40, "quantite: {}".format(quantite))
                    c.drawString(100, y - 60, "Bénéfices: {}".format(bénéfices))
                    # Add more content as needed

                    y -= 60  # Adjust the position for the next content

                    # Add space after the separator
                    y -= 10

                    # Add a separator between each set of data
                    c.line(50, y, 550, y)

                    y -= 20  # Adjust the position for the next content

                # Save the PDF document
                c.save()

            def stat_livri():
                    try:

                        cursor = con.cursor()
                        cursor.execute(f"SELECT * FROM vlivr")
                        valeurs = cursor.fetchall()
                        cursor.close()

                        # Obtenir les noms des champs de la table sélectionnée
                        cursor = con.cursor()
                        cursor.execute(f"SHOW COLUMNS FROM vlivr")
                        champs = [champ[0] for champ in cursor.fetchall()]
                        cursor.close()

                        # Créer une nouvelle fenêtre pour afficher les valeurs
                        stat_fenetre = tk.Toplevel(autre_fenetre)
                        stat_fenetre.title(f"statistique des livraison")
                        stat_fenetre.geometry("600x200")

                        # Créer une zone de texte pour afficher les valeurs avec les noms des champs
                        stat_text = tk.Text(stat_fenetre, width=150, height=20)
                        stat_text.pack()

                        # Afficher les noms des champs
                        stat_text.insert(tk.END, "\t\t".join(champs) + "\n")

                        # Afficher les valeurs avec les noms des champs
                        for valeur in valeurs:
                            stat_text.insert(tk.END, "\t\t        ".join(str(v) for v in valeur) + "\n")

                        cursor = con.cursor()
                        cursor.execute("SELECT Id_Livraison, `Combien de fois livrer`, bénéfices FROM vlivr")
                        result = cursor.fetchall()
                        cursor.close()

                        generate_invoice_livrasion_pdf(result)

                        messagebox.showinfo("Facture générée", "Le fichier PDF des factures a été généré avec succès!")

                    except mysql.Error as e:
                        messagebox.showerror("Erreur", f"Erreur lors de la récupération des valeurs : {e}")


            def stat_prod():
                try:
                    # Fetch the data from the vprod view
                    cursor = con.cursor()
                    cursor.execute("SELECT * FROM vprod")
                    valeurs = cursor.fetchall()
                    cursor.close()

                    # Get the field names of the selected table
                    cursor = con.cursor()
                    cursor.execute("SHOW COLUMNS FROM vprod")
                    champs = [champ[0] for champ in cursor.fetchall()]
                    cursor.close()

                    # Create a new window to display the values
                    stat_fenetre = tk.Toplevel(autre_fenetre)
                    stat_fenetre.title("Statistique des produits")
                    stat_fenetre.geometry("600x200")

                    # Create a text area to display the values with field names
                    stat_text = tk.Text(stat_fenetre, width=150, height=20)
                    stat_text.pack()

                    # Display the field names
                    stat_text.insert(tk.END, "\t\t".join(champs) + "\n")

                    # Display the values with field names
                    for valeur in valeurs:
                        stat_text.insert(tk.END, "\t\t".join(str(v) for v in valeur) + "\n")

                    cursor = con.cursor()
                    cursor.execute("SELECT Id_Article, nom, quntite ,bénéfices FROM vprod")
                    result = cursor.fetchall()
                    cursor.close()

                    generate_invoice_produit_pdf(result)

                    messagebox.showinfo("Facture générée", "Le fichier PDF des factures a été généré avec succès!")

                except mysql.Error as e:
                    messagebox.showerror("Erreur", f"Erreur lors de la récupération des valeurs : {e}")

            def statistique():
                fenetre_stat = tk.Toplevel(fenetre)
                fenetre_stat.title("Affichage de statistique")
                fenetre_stat.geometry("300x150")
                fenetre_stat.configure(bg="slategray2")
                fenetre_stat.resizable(height=False, width=False)  

                stat_prod_button = tk.Button(fenetre_stat, text="statistique des produits", command=stat_prod, font=("Arial", 12), bg="#F0F0F8", relief="solid", borderwidth=1)
                stat_prod_button.grid(row=0, column=0,padx=60 ,pady=20)

                stat_livri_button = tk.Button(fenetre_stat, text="statistique des livraison", command=stat_livri, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                stat_livri_button.grid(row=1, column=0,padx=60, sticky="ew")

            def afficher_valeurs():
                # Obtenir le nom de la table sélectionnée dans la liste déroulante
                selected_table = table_listbox.get(tk.ACTIVE)

                if selected_table:
                    try:
                        cursor = con.cursor()
                        cursor.execute(f"SELECT * FROM {selected_table}")
                        valeurs = cursor.fetchall()
                        cursor.close()

                        # Obtenir les noms des champs de la table sélectionnée
                        cursor = con.cursor()
                        cursor.execute(f"SHOW COLUMNS FROM {selected_table}")
                        champs = [champ[0] for champ in cursor.fetchall()]
                        cursor.close()

                        # Créer une nouvelle fenêtre pour afficher les valeurs
                        valeurs_fenetre = tk.Toplevel(autre_fenetre)
                        valeurs_fenetre.title(f"Valeurs de la table >{selected_table}< ")
                        valeurs_fenetre.geometry("900x400")

                        # Créer une zone de texte pour afficher les valeurs avec les noms des champs
                        valeurs_text = tk.Text(valeurs_fenetre, width=150, height=20)
                        valeurs_text.pack()

                        # Afficher les noms des champs
                        valeurs_text.insert(tk.END, "\t\t".join(champs) + "\n")

                        # Afficher les valeurs avec les noms des champs
                        for valeur in valeurs:
                            valeurs_text.insert(tk.END, "\t\t".join(str(v) for v in valeur) + "\n")

                    except mysql.Error as e:
                        messagebox.showerror("Erreur", f"Erreur lors de la récupération des valeurs : {e}")

                else:
                    messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table pour afficher les valeurs.")

            # Fonction pour ouvrir la fenêtre de gestion des champs
            def ouvrir_gestion_champs(table_name):
                afficher_valeurs()
                fenetre_gestion_champs = tk.Toplevel(fenetre)
                fenetre_gestion_champs.title("Gestion des Champs")
                fenetre_gestion_champs.geometry("400x500")
                fenetre_gestion_champs.configure(bg="slategray2")
                fenetre_gestion_champs.resizable(height=False, width=False)

                label_table_name = tk.Label(fenetre_gestion_champs, text=f"Table : {table_name}")
                label_table_name.pack()

                def inserer_champ():
                    # Demander à l'utilisateur les valeurs à insérer pour chaque champ
                    valeurs = []
                    champs_info = []

                    for champ in champs_listbox.get(0, tk.END):
                        cursor = con.cursor()
                        cursor.execute(f"DESCRIBE {table_name} {champ}")
                        champ_info = cursor.fetchone()
                        cursor.close()

                        valeur = askstring("Insertion de valeur", f"Valeur pour le champ {champ} ({champ_info[1]}) :")
                        valeurs.append(valeur)
                        champs_info.append(champ_info)

                    # Insérer les valeurs dans la base de données
                    try:
                        champs = ', '.join([champ[0] for champ in champs_info])
                        placeholders = ', '.join(['%s'] * len(valeurs))
                        sql_query = f"INSERT INTO {table_name} ({champs}) VALUES ({placeholders})"
                        cursor = con.cursor()
                        cursor.execute(sql_query, tuple(valeurs))
                        con.commit()
                        cursor.close()

                        messagebox.showinfo("Insertion de valeurs", "Les valeurs ont été insérées avec succès !")
                    except mysql.Error as e:
                        messagebox.showerror("Erreur", f"Erreur lors de l'insertion des valeurs : {e}")

                def ouvrir_fenetre_suppression():
                    selected_table = table_name

                    def supprimer_toutes_valeurs():
                        nonlocal selected_table

                        if selected_table:
                            try:
                                confirmation = messagebox.askyesno("Confirmation", "Êtes-vous sûr de vouloir supprimer toutes les valeurs ?")

                                if confirmation:
                                    cursor = con.cursor()
                                    cursor.execute(f"DELETE FROM {selected_table}")
                                    con.commit()
                                    cursor.close()

                                    messagebox.showinfo("Suppression réussie", "Toutes les valeurs ont été supprimées.")

                            except mysql.Error as e:
                                messagebox.showerror("Erreur", f"Erreur lors de la suppression des valeurs : {e}")

                        else:
                            messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table pour supprimer les valeurs.")

                    def supprimer_tuple_condition():
                        nonlocal selected_table

                        if selected_table:
                            try:
                                condition = askstring("Suppression de tuple", "Condition de suppression (WHERE clause) :")

                                if condition:
                                    cursor = con.cursor()
                                    cursor.execute(f"DELETE FROM {selected_table} WHERE {condition}")
                                    con.commit()
                                    cursor.close()

                                    messagebox.showinfo("Suppression réussie", "Le tuple a été supprimé avec succès.")

                            except mysql.Error as e:
                                messagebox.showerror("Erreur", f"Erreur lors de la suppression du tuple : {e}")

                        else:
                            messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table pour supprimer les valeurs.")

                    if selected_table:
                        # Créer une nouvelle fenêtre pour afficher les valeurs
                        valeurs_fenetre = tk.Toplevel(fenetre_gestion_champs)
                        valeurs_fenetre.title(f"Valeurs de la table {selected_table}")
                        valeurs_fenetre.geometry("400x200")
                        valeurs_fenetre.configure(bg="slategray2")
                        valeurs_fenetre.resizable(height=False, width=False)

                        # Afficher les valeurs déjà insérées
                        valeurs_label = tk.Label(valeurs_fenetre, text="fenetre suppression :")
                        valeurs_label.pack()


                        # Créer un bouton pour supprimer toutes les valeurs
                        supprimer_toutes_button = tk.Button(valeurs_fenetre, text="Supprimer toutes les valeurs", command=supprimer_toutes_valeurs, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                        supprimer_toutes_button.pack(pady=20)

                        # Créer un bouton pour supprimer un tuple par condition
                        supprimer_tuple_button = tk.Button(valeurs_fenetre, text="Supprimer un tuple par condition", command=supprimer_tuple_condition, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                        supprimer_tuple_button.pack(pady=10)

                    else:
                        messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table pour afficher les valeurs.")

                def modifier_champ():
                    # Récupérer le champ sélectionné
                    champ_selectionne = champs_listbox.get(champs_listbox.curselection())

                    if champ_selectionne:
                        # Demander à l'utilisateur la nouvelle valeur
                        nouvelle_valeur = askstring("Modification de valeur", f"Nouvelle valeur pour le champ {champ_selectionne} :")

                        if nouvelle_valeur is not None:
                            # Demander à l'utilisateur la condition de mise à jour
                            condition = askstring("Condition de mise à jour", "Condition (WHERE clause) :")

                            if condition:
                                try:
                                    cursor = con.cursor()
                                    cursor.execute(f"UPDATE {table_name} SET {champ_selectionne} = %s WHERE {condition}", (nouvelle_valeur,))
                                    cursor.execute("COMMIT")
                                    cursor.close()

                                    messagebox.showinfo("Modification réussie", "Le champ a été modifié avec succès !")
                                except mysql.Error as e:
                                    messagebox.showerror("Erreur", f"Erreur lors de la modification du champ : {e}")
                            else:
                                messagebox.showwarning("Condition manquante", "Veuillez spécifier une condition pour la mise à jour.")
                    else:
                        messagebox.showwarning("Aucun champ sélectionné", "Veuillez sélectionner un champ à modifier.")
                    

                # Fonction pour chercher les tuples en fonction des conditions saisies
                def chercher_tuples():

                    if table_name:
                        # Demander à l'utilisateur les conditions de recherche
                        conditions = askstring("Recherche de tuples", "Conditions de recherche (WHERE clause) :")

                        if conditions:
                            try:
                                # Exécuter la requête SQL pour chercher les tuples en fonction des conditions
                                cursor = con.cursor()
                                cursor.execute(f"SELECT * FROM {table_name} WHERE {conditions}")
                                tuples = cursor.fetchall()
                                cursor.close()

                                if tuples:
                                    
                                     # Afficher les tuples dans une nouvelle fenêtre
                                    fenetre_tuples = tk.Toplevel(fenetre_gestion_champs)
                                    fenetre_tuples.title("Résultat de la recherche")
                                    fenetre_tuples.geometry("600x300")


                                    # Créer une zone de texte pour afficher les valeurs avec les noms des champs
                                    valeurs_tuples_text = tk.Text(fenetre_tuples)
                                    valeurs_tuples_text.pack()

                                    # Obtenir les noms des champs de la table sélectionnée
                                    cursor = con.cursor()
                                    cursor.execute(f"SHOW COLUMNS FROM {table_name}")
                                    champs = [champ[0] for champ in cursor.fetchall()]
                                    cursor.close()


                                    # Afficher les noms des champs
                                    valeurs_tuples_text.insert(tk.END, "\t\t".join(champs) + "\n")

                                    # Afficher les valeurs avec les noms des champs
                                    for row in tuples:
                                        valeurs_tuples_text.insert(tk.END, "\t\t".join(str(v) for v in row) + "\n")

                                else:
                                    messagebox.showinfo("Résultat de la recherche", "Aucun tuple trouvé pour les conditions spécifiées.")

                            except mysql.Error as e:
                                messagebox.showerror("Erreur", f"Erreur lors de la recherche des tuples : {e}")

                    else:
                        messagebox.showwarning("Aucune table sélectionnée", "Veuillez sélectionner une table pour effectuer la recherche.")
                
                # Bouton pour afficher les valeurs
                afficher_valeurs_button = tk.Button(fenetre_gestion_champs, text="Lister", command=afficher_valeurs,font=("Arial", 12), relief="solid", borderwidth=1)
                afficher_valeurs_button.pack(pady=10)


                # Récupérer les champs de la table sélectionnée
                cursor = con.cursor()
                cursor.execute(f"DESCRIBE {table_name}")
                fields = cursor.fetchall()
                cursor.close()

                # Listbox pour afficher les champs de la table
                champs_listbox = tk.Listbox(fenetre_gestion_champs,relief="solid", borderwidth=2)
                champs_listbox.pack(pady=10)
                champs_listbox.configure(background="#F0F0F8")

                for field in fields:
                    champs_listbox.insert(tk.END, field[0])

                # Créer le bouton d'insertion de champ
                bouton_inserer_champ = tk.Button(fenetre_gestion_champs, text="Insérer un champ", command=inserer_champ, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                bouton_inserer_champ.pack(pady=10)

                # Créer le bouton d'ouverture de fenêtre de suppression
                bouton_suppression = tk.Button(fenetre_gestion_champs, text="Suppression des valeurs", command=ouvrir_fenetre_suppression, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                bouton_suppression.pack(pady=10)

                # Créer le bouton de modification de champ
                bouton_modifier = tk.Button(fenetre_gestion_champs, text="Modifier le champ", command=modifier_champ, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                bouton_modifier.pack(pady=10)

                # Créer le bouton Chercher
                bouton_chercher = tk.Button(fenetre_gestion_champs, text="Chercher", command=chercher_tuples, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
                bouton_chercher.pack(pady=10)



            # Élément dans la nouvelle fenêtre
            button_selection = tk.Button(autre_fenetre, text="Obtenir les tables", command=obtenir_tables,font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            button_selection.pack(pady=10)

            # Élément pour afficher les noms des tables
            message_label_tables = tk.Label(autre_fenetre, text="",font=("Arial", 12))
            message_label_tables.pack()

            # Liste déroulante pour les noms des tables
            table_listbox = tk.Listbox(autre_fenetre, width=50, highlightthickness=1,relief="solid", borderwidth=2)
            table_listbox.pack()


            button_frame = tk.Frame(autre_fenetre, bg="slategray2")  # Couleur de fond blanche
            button_frame.pack(pady=10)


            create_table_button = tk.Button(button_frame, text="Créer table", command=creer_table, font=("Arial", 12), bg="#F0F0F8", relief="solid", borderwidth=1)
            create_table_button.grid(row=0, column=0, padx=25, pady=10, sticky="ew")

            delete_table_button = tk.Button(button_frame, text="Supprimer table", command=supprimer_table, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            delete_table_button.grid(row=0, column=1, pady=10, sticky="ew")

            modify_table_button = tk.Button(button_frame, text="Modifier table", command=modifier_table, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            modify_table_button.grid(row=1, column=0, padx=25,pady=10, sticky="ew")

            afficher_valeurs_button = tk.Button(button_frame, text="Valeurs", command=afficher_valeurs, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            afficher_valeurs_button.grid(row=1, column=1, pady=10, sticky="ew")

            bouton_gestion_champs = tk.Button(button_frame, text="Gestion des Champs", command=lambda: ouvrir_gestion_champs(table_listbox.get(tk.ACTIVE)), font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            bouton_gestion_champs.grid(row=2, column=0, columnspan=2, pady=10, sticky="ew")

            bouton_gestion_champs = tk.Button(button_frame, text="Afichage de Statistique", command=statistique, font=("Arial", 12),bg="#F0F0F8", relief="solid", borderwidth=1)
            bouton_gestion_champs.grid(row=3, column=0, columnspan=2, pady=10, sticky="ew")


    except mysql.Error as e:
        message_label.config(text=f"Erreur lors de la connexion : {e}")

# Chemin vers votre image de fond
image_path = "d.jpg"
image = Image.open(image_path)

# Redimensionner l'image à la taille de la fenêtre
width,height=600, 400
image = image.resize((600,400))


# Création de la fenêtre Tkinter
fenetre = tk.Tk()
fenetre.geometry('600x400')
fenetre.title('Stock Management')
fenetre.resizable(height=False, width=False)

# Création d'un Canvas pour afficher l'image de fond
canvas = tk.Canvas(fenetre, width=width, height=height)
canvas.pack()

# Affichage de l'image de fond sur le Canvas
image_tk = ImageTk.PhotoImage(image)
canvas.create_image(0, 0, anchor=tk.NW, image=image_tk)


# Création du bouton de connexion
bouton_connexion = tk.Button(fenetre, text="Connect to Database", command=se_connecter, font=("Arial", 15))
canvas.create_window(width/2, height/2 - 40, anchor=tk.CENTER, window=bouton_connexion)

# Étiquette pour afficher les messages
message_label = tk.Label(fenetre, text="", font=("Arial", 12))
canvas.create_window(width/2, height/2, anchor=tk.CENTER, window=message_label)

# Création du bouton de déconnexion
exit_button = tk.Button(fenetre, text="Disconnect", command=fenetre.quit, font=("Arial", 15))
canvas.create_window(width/2, height/2 + 40, anchor=tk.CENTER, window=exit_button)

# Exécution de la boucle principale Tkinter
fenetre.mainloop()


