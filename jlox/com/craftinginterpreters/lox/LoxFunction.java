package com.craftinginterpreters.lox;
import java.util.List;

class LoxFunction implements LoxCallable {
    private final Stmt.Function declaration;
    private final Environment closure;
    LoxFunction(Stmt.Function declaration, Environment closure) {
        this.declaration = declaration;
        this.closure = closure;
    }

    @Override
    public Object call(Interpreter interpreter, List<Object> arguments) {
        // shouldn't this be a copy? Is it not possible to modify this?
        // that could be some cool dynamic programming though...
        // > Alas, in our rush to cram closures in, we have let a tiny bit of dynamic scoping leak into the interpreter.
        // > In the next chapter, we will explore deeper into lexical scope and close that hole.
        // Uhh... That's kinda cool though. Why not.
        // Update: it was not cool. And Nystrom resolved it. In a resolver. 😏
        Environment environment = new Environment(closure);
        for (int i = 0; i < declaration.params.size(); i++) {
            environment.define(declaration.params.get(i).lexeme, arguments.get(i)); // c😎😎😎l
        }
        try {
            interpreter.executeBlock(declaration.body, environment);
        } catch (Return returnValue) {
            return returnValue.value;
        }

        return null;
    }

    @Override
    public int arity() {
        return declaration.params.size();
    }

    @Override
    public String toString() {
        return "<fn " + declaration.name.lexeme + ">";
    }
}
