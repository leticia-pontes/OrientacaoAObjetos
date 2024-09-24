document.addEventListener('DOMContentLoaded', function() {
// Função para calcular o total -> pagina alimentação
    function calcularTotal() {
        const selects = document.querySelectorAll('.refeicao-item select[name="quantidade"]');
        let total = 0;


        selects.forEach(select => {
            total += parseInt(select.value);
        });

        document.getElementById("total-value").querySelector('h3').textContent = total + 'g';
    }

    document.querySelectorAll('.refeicao-item select[name="quantidade"]').forEach(select => {
        select.addEventListener('change', calcularTotal);
    });


    calcularTotal();

    class Navegador {
        constructor(elementId, page) {
            this.element = document.getElementById(elementId);
            this.page = page;
        }

        navegar() {
            window.location.href = this.page;
        }
    }

    const alimentacaoNav = new Navegador("botaoAlimentacao", "paginaalimentacao.html");
    const principalNav = new Navegador("botaoPrincipal", "paginaprincipal.html");
    const saudeNav = new Navegador("botaoSaude", "paginasaude.html");

    document.getElementById("botaoAlimentacao").addEventListener("click", function() {
        alimentacaoNav.navegar();
    });

    document.getElementById("botaoPrincipal").addEventListener("click", function() {
        principalNav.navegar();
    });

    document.getElementById("botaoSaude").addEventListener("click", function() {
        saudeNav.navegar();
    });

});
