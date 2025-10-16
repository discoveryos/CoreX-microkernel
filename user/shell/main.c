int main() {
    char key;
    while (1) {
        if (read(STDIN, &key, 1)) {
            if (key == '\n') execute_command();
            else echo_to_screen(key);
        }
    }
}
