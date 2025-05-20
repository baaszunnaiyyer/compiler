$$
\begin{align}
    [\text{prog}] &\to [\text{stmt}^*]
    \\
    [\text{stmt}] &\to
    \begin{cases}
        exit([\text{expr}]) \\
        have\space \text{identifier} = \text{[expr]};
    \end{cases}
    \\
    [\text{expr}] &\to 
    \begin{cases}
        \text{int_lit} \\
        \text{ident}
    \end{cases}
\end{align}
$$
