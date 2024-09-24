package Java;
public class metodos {
    static class Horario {
        protected int horas;
        protected int minutos;
        protected int segundos;

        public Horario(int horas, int minutos, int segundos) {
            this.horas = horas;
            this.minutos = minutos;
            this.segundos = segundos;
        }

        @Override
        public String toString() {
            return String.format(
                "{ horas = %d , minutos = %d , segundos = %d }", horas, minutos, segundos
            );
        }
    }

    public static void main(String...args) {
        Horario hora_atual = new Horario(12, 35, 54);
        System.out.println(hora_atual);
    }
}