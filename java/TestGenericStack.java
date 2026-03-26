public class TestGenericStack {
    public static void main(String[] args) {
        GenericStack<String> stack = new GenericStack<>();
        
        System.out.println("Добовляем 20 элементов: ");
        for (int i = 1; i <= 20; i++){
            stack.push("Элемент: " + i);
        }

        System.out.println(stack);
        System.out.println("Размер: " + stack.getSize());
        System.out.println("Верхний: " + stack.peek());

        System.out.println("Извлекаем 5 элементов");
        for (int i = 0; i < 5; i ++){
            System.out.println("Извлечен: " + stack.pop());


        }

        System.out.println("\nОсталось: " + stack.pop());
        System.out.println("Размер: " + stack.getSize());


        GenericStack<Integer> intStack = new GenericStack<>();
        intStack.push(1);
        intStack.push(2);
        intStack.push(3);
        System.out.println("\nСтек с числами: " + intStack);
    }
}
