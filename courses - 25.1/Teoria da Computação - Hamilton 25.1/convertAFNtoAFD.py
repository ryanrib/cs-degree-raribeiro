from collections import defaultdict

class AFNtoAFDConverter:
    def __init__(self, states, alphabet, transitions, start_state, final_states):
        self.states = states  # Conjunto de estados {q1, q2, q3, ...}
        self.alphabet = alphabet  # Alfabeto {0,1} ou {a,b,c}
        self.transitions = transitions  # Transições { (estado, símbolo) : {conjunto de estados} }
        self.start_state = start_state  # Estado inicial
        self.final_states = final_states  # Estados finais
        self.afd_transitions = {}  # Transições do AFD

    def epsilon_closure(self, state):
        """Calcula o fecho-ε de um estado."""
        closure = set([state])
        stack = [state]
        while stack:
            curr_state = stack.pop()
            if (curr_state, '') in self.transitions:  # Se há transição por ε
                for next_state in self.transitions[(curr_state, '')]:
                    if next_state not in closure:
                        closure.add(next_state)
                        stack.append(next_state)
        return closure

    def move(self, states, symbol):
        """Retorna o conjunto de estados alcançáveis a partir de um conjunto de estados com um símbolo."""
        reachable = set()
        for state in states:
            if (state, symbol) in self.transitions:
                reachable.update(self.transitions[(state, symbol)])
        return reachable

    def convert(self):
        """Converte o AFN-ε em um AFD."""
        # 1. Calcula o fecho-ε do estado inicial
        initial_closure = frozenset(self.epsilon_closure(self.start_state))
        afd_states = {initial_closure}  # Conjunto de estados do AFD
        unprocessed_states = [initial_closure]  # Lista de estados a processar
        state_mapping = {initial_closure: 'S0'}  # Mapeia conjuntos de estados para nomes do AFD
        afd_final_states = set()

        while unprocessed_states:
            current = unprocessed_states.pop(0)
            current_name = state_mapping[current]
            self.afd_transitions[current_name] = {}

            for symbol in self.alphabet:
                # 2. Aplica "move" e "epsilon-closure"
                move_result = self.move(current, symbol)
                closure_result = frozenset(
                    state for s in move_result for state in self.epsilon_closure(s)
                )

                if closure_result:
                    if closure_result not in afd_states:
                        afd_states.add(closure_result)
                        unprocessed_states.append(closure_result)
                        state_mapping[closure_result] = f"S{len(state_mapping)}"

                    # Adiciona a transição ao AFD
                    self.afd_transitions[current_name][symbol] = state_mapping[closure_result]

            # 3. Define os estados finais do AFD
            if any(state in self.final_states for state in current):
                afd_final_states.add(current_name)

        return {
            "states": set(state_mapping.values()),
            "alphabet": self.alphabet,
            "transitions": self.afd_transitions,
            "start_state": state_mapping[initial_closure],
            "final_states": afd_final_states
        }

# Exemplo de uso
states = {'q1', 'q2', 'q3', 'q4'}
alphabet = {'0', '1'}
transitions = {
    ('q1', '0'): {'q1'}, 
    ('q1', '1'): {'q2'},
    ('q2', '0'): {'q3'}, 
    ('q2', ''): {'q3'},  # ε-transição
    ('q3', '0'): {'q4'},
    ('q3', ''): {'q4'},  # ε-transição
    ('q4', '1'): {'q4'}
}
start_state = 'q1'
final_states = {'q4'}

converter = AFNtoAFDConverter(states, alphabet, transitions, start_state, final_states)
afd_result = converter.convert()

# Exibir o resultado
print("Estados do AFD:", afd_result["states"])
print("Transições do AFD:")
for state, trans in afd_result["transitions"].items():
    print(f"  {state}: {trans}")
print("Estado inicial do AFD:", afd_result["start_state"])
print("Estados finais do AFD:", afd_result["final_states"])
