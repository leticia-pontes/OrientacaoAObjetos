def opcao0():
    print("Opção 0")

def opcao1():
    print("Opção 1")

def desconhecido():
    print("Opção desconhecida")

menu = {
    0: opcao0,
    1: opcao1,
}

def adicionar_opcoes(menu:dict):
    menu[2] = lambda : print("Opção 2")
    menu[3] = lambda : print("Opção 3")

if __name__ == '__main__':
    adicionar_opcoes(menu)
    opcao = 2
    acao = menu.get(opcao, desconhecido)
    acao()