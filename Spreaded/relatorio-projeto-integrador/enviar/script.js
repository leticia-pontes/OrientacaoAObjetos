console.log("O script está sendo executado");

class Editor {
    constructor(elementId) {
        this.element = document.getElementById(elementId);
    }

    editar() {
        var novoValor = prompt(`Digite o novo valor para ${this.element.id}:`);
        if (novoValor !== null) {
            this.element.textContent = novoValor;
        }
    }
}

class Navegador {
    constructor(elementId, page) {
        this.element = document.getElementById(elementId);
        this.page = page;
    }

    navegar() {
        window.location.href = this.page;
    }
}

// Instanciando objetos para edição
const idadeEditor = new Editor("idade");
const pesoEditor = new Editor("peso");
const racaEditor = new Editor("raça");
const corEditor = new Editor("cor");

// Adicionando event listeners para edição
document.getElementById("editarIdade").addEventListener("click", function() {
    idadeEditor.editar();
});

document.getElementById("editarPeso").addEventListener("click", function() {
    pesoEditor.editar();
});

document.getElementById("editarRaca").addEventListener("click", function() {
    racaEditor.editar();
});

document.getElementById("editarCor").addEventListener("click", function() {
    corEditor.editar();
});

// Instanciando objetos para navegação
const alimentacaoNav = new Navegador("botaoAlimentacao", "paginaalimentacao.html");
const principalNav = new Navegador("botaoPrincipal", "paginaprincipal.html");
const saudeNav = new Navegador("botaoSaude", "paginasaude.html");

// Adicionando event listeners para navegação
document.getElementById("botaoAlimentacao").addEventListener("click", function() {
    alimentacaoNav.navegar();
});

document.getElementById("botaoPrincipal").addEventListener("click", function() {
    principalNav.navegar();
});

document.getElementById("botaoSaude").addEventListener("click", function() {
    saudeNav.navegar();
});


