public class GenericStack<E> {
    private static final int DEFAULT_SIZE = 16;
    private E[] arr;
    private int size;
    
    @SuppressWarnings("unchecked")
    public GenericStack() {
        arr = (E[]) new Object[DEFAULT_SIZE];
        size = 0;
    }
    
    public int getSize() {
        return size;
    }
    
    public E peek() {
        if (isEmpty()) {
            return null;
        }
        return arr[size - 1];
    }
    
    public void push(E o) {
        if (size == arr.length) {
            resizeArray();
        }
        arr[size] = o;
        size++;
    }
    
    public E pop() {
        if (isEmpty()) {
            return null;
        }
        E o = arr[size - 1];
        arr[size - 1] = null;
        size--;
        return o;
    }
    
    public boolean isEmpty() {
        return size == 0;
    }
    
    @SuppressWarnings("unchecked")
    private void resizeArray() {
        int newSize = arr.length * 2;
        E[] newArr = (E[]) new Object[newSize];
        for (int i = 0; i < arr.length; i++) {
            newArr[i] = arr[i];
        }
        arr = newArr;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("стек: [");
        for (int i = 0; i < size; i++) {
            sb.append(arr[i]);
            if (i < size - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }
}
