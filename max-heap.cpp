#include <iostream>
#include <vector>
#include <utility>   // Para std::swap
#include <stdexcept> // Para runtime_error

using namespace std;

// Classe que encapsula o Binary Heap (Max-Heap) e o Heapsort
class MaxHeapBinaria {
private:
    vector<int> heap; // Vetor que armazena os nós da árvore quase completa
    int tamanho;      // Quantidade de elementos atualmente no heap
    int capacidade;   // Capacidade máxima reservada

    // Procedimento para manter a propriedade descendo o elemento (O(log n))
    void heapify(int indice) {
        int maior = indice;
        int filho_esquerda = 2 * indice + 1; // Índice do filho à esquerda (base 0)
        int filho_direita  = 2 * indice + 2; // Índice do filho à direita (base 0)

        // Compara com o filho da esquerda: procura se ele é MAIOR
        if (filho_esquerda < tamanho && heap[filho_esquerda] > heap[maior]) {
            maior = filho_esquerda;
        }

        // Compara com o filho da direita: procura se ele é MAIOR
        if (filho_direita < tamanho && heap[filho_direita] > heap[maior]) {
            maior = filho_direita;
        }

        // Se o maior elemento não for o próprio índice, troca e desce recursivamente
        if (maior != indice) {
            trocar(indice, maior);
            heapify(maior);
        }
    }

    // Função utilitária para trocar dois elementos de posição no arranjo
    void trocar(int i, int j) {
        swap(heap[i], heap[j]);
    }

public:
    // Construtor: aloca o espaço com base na capacidade informada
    MaxHeapBinaria(int cap) {
        capacidade = cap;
        tamanho = 0;
        heap.resize(capacidade);
    }

    // Retorna a quantidade de elementos válidos no heap
    int obter_tamanho() const {
        return tamanho;
    }

    // Insere um novo elemento no Heap (O(log n))
    void inserir(int valor) {
        if (tamanho == capacidade) {
            throw runtime_error("Erro: O Heap está cheio!");
        }

        // Adiciona o novo valor na primeira posição livre (final do heap)
        int indice_atual = tamanho;
        heap[indice_atual] = valor;
        tamanho++;

        // Flutua para cima: enquanto não for a raiz e for MAIOR que o pai
        while (indice_atual > 0 && heap[indice_atual] > heap[(indice_atual - 1) / 2]) {
            trocar(indice_atual, (indice_atual - 1) / 2);
            indice_atual = (indice_atual - 1) / 2; // Sobe para o índice do pai
        }
    }

    // Retorna o elemento da raiz sem remover (O(1))
    int obter_raiz() const {
        if (tamanho == 0) {
            throw runtime_error("Erro: O Heap está vazio!");
        }
        return heap[0];
    }

    // Remove e retorna o elemento da raiz (O(log n))
    int remover_raiz() {
        if (tamanho == 0) {
            throw runtime_error("Erro: O Heap está vazio!");
        }

        int valor_raiz = heap[0]; // A raiz sempre armazena o maior valor

        // Substitui a raiz pelo último elemento e reduz o tamanho
        heap[0] = heap[tamanho - 1];
        tamanho--;

        // Restabelece a propriedade de Max-Heap a partir da nova raiz
        heapify(0);

        return valor_raiz;
    }

    // Algoritmo de Ordenação Heapsort (O(n log n)) -> Resulta em ordem CRESCENTE
    void heap_sort() {
        // Passo 1: Constrói o Max-Heap (Build-Heap) de baixo para cima
        for (int i = tamanho / 2 - 1; i >= 0; i--) {
            heapify(i);
        }

        // Passo 2: Extrai a raiz sucessivamente para o final do arranjo
        for (int i = tamanho - 1; i >= 0; i--) {
            trocar(0, i);
            tamanho = i; // Isola o maior elemento já posicionado no final
            heapify(0);
        }
    }

    // Imprime os elementos no arranjo
    void imprimir(int limite = -1) const {
        int n = (limite == -1) ? tamanho : limite;
        for (int i = 0; i < n; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};



int main() {
    vector<int> arranjo = { 7, 3, 9, 2, 4, 1, 5 };

    cout << "=== DEMONSTRACAO DA MAX-HEAP ===" << endl;
    cout << "Vetor original a ser inserido: ";
    for (int num : arranjo) cout << num << " ";
    cout << "\n\n";

    // 1. Cria a Max-Heap e insere os elementos
    MaxHeapBinaria max_heap(arranjo.size());
    for (int num : arranjo) {
        max_heap.inserir(num);
    }

    cout << "Arranjo interno estruturado como Max-Heap: ";
    max_heap.imprimir();

    // 2. Consulta da raiz
    cout << "Maior elemento atual (raiz): " << max_heap.obter_raiz() << endl;

    // 3. Remocao do elemento de maior prioridade
    cout << "Removendo o maior elemento: " << max_heap.remover_raiz() << endl;
    cout << "Max-Heap apos a remocao: ";
    max_heap.imprimir();

    // 4. Teste de ordenacao completa via Heapsort
    // Reinserindo o elemento para restaurar o vetor completo
    max_heap.inserir(9);
    cout << "\nExecutando Heapsort (ordem crescente)..." << endl;
    max_heap.heap_sort();
    cout << "Vetor totalmente ordenado: ";
    max_heap.imprimir(arranjo.size());

    return 0;
}
