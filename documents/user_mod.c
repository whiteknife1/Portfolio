/*

Kernal mapped to 0x80_0000_0000


*/

uint32_t program_counter;
uint32_t stack_pointer;
uint32_t program_stack[];
uint8_t program[];

main() {
    setup_stdin_and_stdout();
    puts("Once you get into the Abyss, you have no choice but to keep going down.");
    if (scanf("%1024s", program) == 1) {
        work();
        return 0;
    }
    else
        return 1;
}

work() {
    uint32_t program_strlen = strlen(program);
    int32_t program_counter = 0;

    while(program_counter < program_strlen) {
        if (is_digit(program[program_counter]))
            push(fetch_int());
        else {
            if (    (program[program_counter] <= 0x60)
                 || (program[program_counter] > 0x7a)) {
                if (commands(program[program_counter])) {
                    void (*f) () = commands(program[program_counter]);
                    f();
                }
            }
        }

        program_counter++;
    }
}

/*
This function takes ASCII decimal characters, and puts them on the stack. Needs
to be terminated with a non-decimal character. Use '?'. This works well.
*/
void fetch_int() {}

void push(uint32_t value) {
    if (stack_pointer <= 0x3ff) {
        int64_t sp = (int32_t) stack_pointer;
        program_stack[sp] = value;
        stack_pointer++;
    }
}

uint32_t pop() {
    if (stack_pointer == 0)
        return 0;
    else {
        stack_pointer -= 1;
        int64_t sp = (int32_t) stack_pointer;
        return program_stack[sp];
    }
}

uint32_t pick(int32_t index) {
    if ((index < 0) || (index >= stack_pointer))
        return 0;
    else {
        uint32_t index = stack_pointer - index - 1;
        int64_t sindex = (int32_t) index;
        return program_stack[sindex];
    }
}

void dup_() {
    push(pick(0));
}

void swap_() {
    var_c = program_stack[stack_pointer - 1];
    program_stack[stack_pointer - 1] = program_stack[stack_pointer - 2];
    program_stack[stack_pointer - 2] = var_c;
}


void rot() {
    var_c = program_stack[stack_pointer - 3];
    program_stack[stack_pointer - 3] = program_stack[stack_pointer - 2];
    program_stack[stack_pointer - 2] = program_stack[stack_pointer - 2];
    program_stack[stack_pointer - 1] = var_c;
}

uint32_t pick() {
    push(pick(pop()));
    program_counter += 1;
}

void add() {
    push(pop() + pop());
}

void minus() {
    push(pop() - pop());
}

void mul() {
    push(pop() * pop());
}

void div_() {
    push(pop() / pop());
}

void neg() {
    push(0 - pop());
}

void and_() {
    push(pop() & pop());
}

void or_() {
    push(pop() | pop());
}

void not_() {
    push(~pop());
}

void gt() {
    ebx = pop();
    if (pop() < pop())
        push(0);
    else
        push(0xffffffff);
}

void eql() {
    if (pop() == pop())
        push(0);
    else
        push(0xffffffff);
}

void store() {
    int32_t store_offset = pop();
    if ((store_offset >= 0) && (store_offset <= 0x19)) {
        int64_t offset = (int32_t) store_offset;
        offset += 500;
        program_stack[1 + offset] = pop();
    }
}

void fetch() {
    int32_t fetch_offset = pop();
    if ((fetch_offset >= 0) && (fetch_offset <= 0x19)) {
        int64_t offset = (int32_t) fetch_offset;
        offset += 500;
        push(program_stack[1 + offset]);
    }
}

void write_() {
    uint8_t byte = pop();
    write(1, &byte, 1);
}

void writed() {
    printf("%d\n", pop());
}

/* 90% confidence */
void fetch_int() {
    var_c = 0;
    while (isdigit(program[program_counter])) {
        var_c = (var_c * 10) + program[program_counter];
        program_counter++;
    }
    program_counter++;
    return var_c;
}

void (*) () commands(uint32_t command) {
    void (* rax)() = NULL;
    switch(command) {
    case 0x24: rax = &dup_; break;
    case 0x25: rax = &pop_; break;
    case 0x26: rax = &and_; break;
    case 0x2a: rax = &mul; break;
    case 0x2b: rax = &add; break;
    case 0x2c: rax = &write_; break;
    case 0x2d: rax = &minus; break;
    case 0x2e: rax = &writed; break;
    case 0x2f: rax = &div_; break;
    case 0x3a: rax = &store; break;
    case 0x3b: rax = &fetch; break;
    case 0x3d: rax = &eql; break;
    case 0x3e: rax = &gt; break;
    case 0x40: rax = &rot; break;
    case 0x5c: rax = &swap_; break;
    case 0x5f: rax = &neg; break;
    case 0x7c: rax = &or_; break;
    case 0x7e: rax = &not_; break;
    }
    return rax;
}