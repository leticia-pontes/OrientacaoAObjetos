package Java;
import java.util.Scanner;

public class listas {
    public static void main(String... args) {
        
        try (Scanner scanner = new Scanner(System.in)) {
            int totalAlunos = 10;
            float[] notas = new float[totalAlunos];

            for(int indice = 0; indice < totalAlunos; indice++) {
                System.out.println("Digite a nota do aluno " + indice);
                float nota = scanner.nextFloat();
                notas[indice] = nota;
            }

            float media = 0;
            for (int indice = 0; indice < totalAlunos; indice++) {
                media += notas[indice];
            }

            media /= totalAlunos;

            System.out.println("Media: " + media);

            for (int indice = 0; indice < totalAlunos; indice++) {
                if (notas[indice] < media) {
                    System.out.println("Aluno " + indice + " abaixo da media");
                }
            }
        }
    }
}
