#!/usr/bin/env python
import os
import time
import shutil

#Using the os module to get information about a file
def dump(file):
    print ("stat", file)
    st = os.stat(file)
    mode, ino, dev, nlink, uid, gid, size, atime, mtime, ctime = st
    print ("- size:", size, "bytes")
    print ("- owner:", uid, gid)
    print ("- created:", time.ctime(ctime))
    print ( "- last accessed:", time.ctime(atime))
    print ("- last modified:", time.ctime(mtime))
    print ("- mode:", oct(mode))
    print ("- inode/dev:", ino, dev)

#change current directory
def chdir(directory):
    print("Current directory:")
    cwd = os.getcwd()
    print (cwd)
    os.chdir(directory)
    cwd = os.getcwd()
    print("Changed directory:")
    print (cwd)
    

#display current directory
def cudir():
    print("Current directory:")
    cwd = os.getcwd()
    print(cwd)

#Directory changed to parent directory
def pdir():
    print("Directory changed")
    os.chdir(os.pardir)
    print (os.getcwd())

#list elements of directory
def ldir(directory):
    print("Elements of directory:" +directory)
    for file in os.listdir(directory):
        print (file)

#used to list directory elements
def fc(directory):
    os.chdir(directory)

#create directory
def mkd(path):
    os.makedirs(path, exist_ok=True)
    print("Directories created:", path)
 
 
# Commande pour supprimer un fichier ou un répertoire
def rm(path):
    try:
        if os.path.isfile(path):
            os.remove(path)
            print(f"Le fichier '{path}' a été supprimé.")
        elif os.path.isdir(path):
            shutil.rmtree(path)
            print(f"Le répertoire '{path}' et son contenu ont été supprimés.")
        else:
            print(f"Le fichier ou le répertoire '{path}' n'existe pas.")
    except FileNotFoundError:
        print(f"Le fichier ou le répertoire '{path}' n'existe pas.")
    except PermissionError:
        print(f"Permission refusée pour supprimer '{path}'.")


#Return the real group id of the current process.
def rgid():
    
    print( os.getgid() )
 

#return the current process’s user id.
def uid():
     # id=os.getuid()
    print( os.getuid())

#Returns the real process ID of the current process.
def rpid():
    print( os.getpid())
    return  

#Return information identifying the current operating system.
def cos():
    print(os.name)

#delete file
def df(file):
    os.remove(file)
    print(file+" deleted")
    return

# Commande pour afficher le répertoire de travail actuel
def pwd():
    print(os.getcwd())

#specifies OS type
def oname():
    print("OS name is "+os.name)
    return

#used to nename text files 
def rname(filename,newname):
    os.rename(filename,newname)
    print(filename + " renamed to "+ newname)
    return


# Commande pour afficher le contenu d'un répertoire de manière détaillée
def ls():
    files = os.listdir()
    print("permissions \t size \t\t\t file \t\t\t path")
    for file in files:
        path = os.path.abspath(file)
        size = os.path.getsize(file)
        permissions = oct(os.stat(file).st_mode)[-3:]
        print(f"{permissions} \t\t {size} bytes \t\t {file} \t\t {path}")


def sort(file, delimiter, k, rev):
    try:
        if os.path.isfile(file) and os.path.exists(file):
            with open(file) as f:
                lines = f.readlines()
                keyfunc = lambda x: x.strip().split(delimiter)[int(k) - 1]  # Convert k to integer
                sorted_lines = sorted(lines, key=keyfunc, reverse=bool(rev))
                print("".join(sorted_lines))
        else:
            print(file,'not found or not file')
    except:
        print("cas de trier non pris en charge")

        


def cp(src,dest):
    if os.path.isfile(src) and os.path.isdir(dest):

        shutil.copy2(src, dest)
    elif os.path.isfile(src) and (os.path.isfile(dest) or not os.path.exists(dest)):

        shutil.copy2(src, dest)
    elif os.path.isdir(src) and (os.path.isdir(dest) or not os.path.exists(dest)):

        shutil.copytree(src, dest, dirs_exist_ok=True)
    elif not os.path.exists(src):
        print(f"{src} n'existe pas")
    else:
        print("Cas de copie non pris en charge")




def find(dir, word):
    
        for root,dirs,files in os.walk(dir):
            for file in files:
                if word in file:
                    print(os.path.join(root, file))



#used to return size 
def size(file):
    if os.path.isfile(file):
        return format_size(os.path.getsize(file))
    elif os.path.isdir(file):
        total_size = 0
        for path, dirs, files in os.walk(file):
            for f in files:
                file_path = os.path.join(path, f)
                total_size += os.path.getsize(file_path)
        
        return format_size(total_size)
    else:
        return 0
    
# Convertir la taille en utilisant les unités (Ko, Mo, Go)
def format_size(size):
    units = ['octets', 'Ko', 'Mo', 'Go']
    index = 0
    while size >= 1024 and index < len(units) - 1:
        size /= 1024
        index += 1
    return print('{:.2f} {}'.format(size, units[index]))
     
######################################################

    
def wc(file,opt):
    data=''
    try:
        with open(file) as f:
            data=f.read()
    except:
        print(file,'not found or perission denieded')
    c=len(data)
    l=len(data.split('\n')) 
    w=len(data.split())
    if opt=='':
        print(l,w,c,'\t',file)
    elif opt=='l':
        print(l,'\t',file)
    elif opt=='w':
        print(w,'\t',file)
    elif opt=='c':
        print(c,'\t',file)
    else:
        print('syntax error')


def grep(file,word):
    try:
        with open(file) as f:
            for line in f:
                if word in line:
                    print(line.replace(word,'\033[31m'+word+'\033[37m'),end='')
    except:
        print(file,'not found or perission denieded')



def cut(file,delimiter,fields):
    try:  
        with open(file) as f:
            for line in f:
                parts = line.strip().split(delimiter)
                output = []
                for field in fields:
                    if int(field) > len(parts):
                        print(f"{file}: Field {field} not found in line '{line.strip()}'")
                        break
                    output.append(parts[int(field) - 1])
                else:
                    print(delimiter.join(output))
    except:
        print(file,'not found or perission denieded')


# Commande pour créer un fichier vide
def touch(file):
    try:
        with open(file, 'w') as f:
            pass
        print(f"Le fichier '{file}' a été créé.")
    except PermissionError:
        print(f"Permission refusée pour créer le fichier '{file}'.")      
                    
# Commande pour afficher le contenu d'un fichier
def cat(file):
    try:
        with open(file, 'r') as f:
            contents = f.read()
            print(contents)
    except FileNotFoundError:
        print(f"Le fichier '{file}' n'existe pas.")
    except PermissionError:
        print(f"Permission refusée pour accéder au fichier '{file}'.")



def help():
    cmd_color = '\033[91m'  # Code ANSI pour la couleur rouge
    end_color = '\033[0m'   # Code ANSI pour réinitialiser la couleur

    print(f"{cmd_color}dump(file){end_color} - Affiche les informations sur un fichier.")
    print(f"{cmd_color}chdir(directory){end_color} - Change le répertoire de travail courant.")
    print(f"{cmd_color}cudir(){end_color} - Affiche le répertoire de travail courant.")
    print(f"{cmd_color}pdir(){end_color} - Change le répertoire de travail courant vers le répertoire parent.")
    print(f"{cmd_color}pwd(){end_color} - Affiche le répertoire de travail courant.")
    print(f"{cmd_color}ldir(directory){end_color} - Liste les éléments d'un répertoire.")
    print(f"{cmd_color}ldir(){end_color} - Liste les éléments du répertoire de travail courant.")
    print(f"{cmd_color}fc(directory){end_color} - Change le répertoire de travail courant.")
    print(f"{cmd_color}mkd(directory){end_color} - Crée un nouveau répertoire.")
    print(f"{cmd_color}rm(path){end_color} - Supprime un fichier ou un répertoire.")
    print(f"{cmd_color}rgid(){end_color} - Retourne l'ID du groupe réel du processus courant.")
    print(f"{cmd_color}uid(){end_color} - Retourne l'ID de l'utilisateur du processus courant.")
    print(f"{cmd_color}rpid(){end_color} - Retourne l'ID du processus réel du processus courant.")
    print(f"{cmd_color}cos(){end_color} - Retourne des informations sur le système d'exploitation.")
    print(f"{cmd_color}df(file){end_color} - Supprime un fichier.")
    print(f"{cmd_color}oname(){end_color} - Affiche le nom du système d'exploitation.")
    print(f"{cmd_color}rname(filename, newname){end_color} - Renomme un fichier.")
    print(f"{cmd_color}sort(file, delimiter, k, rev){end_color} - Trie les lignes d'un fichier en utilisant une clé et un délimiteur.")
    print(f"{cmd_color}cp(src, dest){end_color} - Copie un fichier ou un répertoire.")
    print(f"{cmd_color}size(file){end_color} - Affiche la taille d'un fichier ou d'un répertoire.")
    print(f"{cmd_color}cut(file, delimiter, fields){end_color} - Extrait des champs d'un fichier en utilisant un délimiteur.")
    print(f"{cmd_color}grep(file, word){end_color} - Recherche un mot dans un fichier et affiche les lignes correspondantes.")
    print(f"{cmd_color}wc(file, opt){end_color} - Compte le nombre de lignes, de mots et de caractères dans un fichier.")
    print(f"{cmd_color}cat(file){end_color} - Affiche le contenu d'un fichier.")
    print(f"{cmd_color}touch(file){end_color} - Crée un nouveau fichier vide.")
    print(f"{cmd_color}help(){end_color} - Affiche l'aide sur les commandes disponibles.")
    print(f"{cmd_color}exit(){end_color} - Quitte le programme.")




# Main execution loop
while True:
    command = input("Enter a command: ")

    if command == "dump":
        file = input("Enter the file path: ")
        dump(file)

    elif command == "chdir":
        directory = input("Enter the directory path: ")
        chdir(directory)

    elif command == "cudir":
        cudir()

    elif command == "pdir":
        pdir()

    elif command == "ldir":
        directory = input("Enter the directory path (optional): ")
        ldir(directory)

    elif command == "fc":
        directory = input("Enter the directory path: ")
        fc(directory)

    elif command == "mkd":
        directory = input("Enter the directory path: ")
        mkd(directory)

    elif command == "rm":
        path = input("Entrez le chemin du fichier ou du répertoire à supprimer : ")
        rm(path)

    elif command == "rgid":
        rgid()
    
    elif command == "pwd":
        pwd()

    elif command == "uid":
        uid()

    elif command == "rpid":
        rpid()

    elif command == "cos":
        cos()

    elif command == "df":
        file = input("Enter the file path: ")
        df(file)

    elif command == "oname":
        oname()

    elif command == "rname":
        filename = input("Enter the current file name: ")
        newname = input("Enter the new file name: ")
        rname(filename, newname)

    elif command == "ls":
        ls()
    
    elif command == "sort":
        filename = input("Enter the file name: ")
        delimiter = input("Enter the delimiter : ")
        k = input("Enter the k : ")
        rev = input("Enter if sort is reversed or not : ")
        sort(filename,delimiter,k,rev)

    elif command == "cp":
        source = input("Enter the srcfile : ")
        destination = input("Enter the destination : ")
        cp(source,destination)

    elif command == "find":
        dir = input("Enter the dir : ")
        word = input("Enter the word  : ")
        find(dir,word)

    elif command == "size":
        path = input("Enter the path : ")
        size(path)

    elif command == "wc":
        filename = input("Enter the file name : ")
        opt = input("Enter the opt [' '/'l'/'w'/'c'] : ")
        wc(filename,opt)

    elif command == "grep":
        filename = input("Enter the file name : ")
        word = input("Enter the word  : ")
        grep(filename,word)

    elif command == "cut":
        filename = input("Enter the file name : ")
        delimiter = input("Enter the delimiter : ")
        fields = input("Enter the fields : ")
        cut(filename,delimiter,fields)

    elif command == "cat":
        file = input("Entrez le chemin du fichier : ")
        cat(file)

    elif command == "touch":
        file = input("Entrez le chemin du fichier : ")
        touch(file)

    elif command == "help":
        help()

    elif command == "exit":
        break

    else:
        print("Invalid command. Type 'help' to see available commands.")