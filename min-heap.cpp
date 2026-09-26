#include <iostream>
#include <vector>
#include <utility>   // Para std::swap
#include <stdexcept> // Para runtime_error

using namespace std;

// Classe que encapsula o Binary Heap (Min-Heap) e o Heapsort
class MinHeapBinaria {
private:
    vector<int> heap; // Vetor que armazena os nós da árvore quase completa
    int tamanho;      // Quantidade de elementos atualmente no heap
    int capacidade;   // Capacidade máxima reservada

    // Procedimento para manter a propriedade descendo o elemento (O(log n))
    void heapify(int indice) {
        int menor = indice;
        int filho_esquerda = 2 * indice + 1; // Índice do filho à esquerda (base 0)
        int filho_direita  = 2 * indice + 2; // Índice do filho à direita (base 0)

        // Compara com o filho da esquerda: procura se ele é MENOR
        if (filho_esquerda < tamanho && heap[filho_esquerda] < heap[menor]) {
            menor = filho_esquerda;
        }

        // Compara com o filho da direita: procura se ele é MENOR
        if (filho_direita < tamanho && heap[filho_direita] < heap[menor]) {
            menor = filho_direita;
        }

        // Se o menor elemento não for o próprio índice, troca e desce recursivamente
        if (menor != indice) {
            trocar(indice, menor);
            heapify(menor);
        }
    }

    // Função utilitária para trocar dois elementos de posição no arranjo
    void trocar(int i, int j) {
        swap(heap[i], heap[j]);
    }

public:
    // Construtor: aloca o espaço com base na capacidade informada
    MinHeapBinaria(int cap) {
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

        // Flutua para cima: enquanto não for a raiz e for MENOR que o pai
        while (indice_atual > 0 && heap[indice_atual] < heap[(indice_atual - 1) / 2]) {
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

        int valor_raiz = heap[0]; // A raiz sempre armazena o menor valor

        // Substitui a raiz pelo último elemento e reduz o tamanho
        heap[0] = heap[tamanho - 1];
        tamanho--;

        // Restabelece a propriedade de Min-Heap a partir da nova raiz
        heapify(0);

        return valor_raiz;
    }

    // Algoritmo de Ordenação Heapsort (O(n log n)) -> Resulta em ordem DECRESCENTE
    void heap_sort() {
        // Passo 1: Constrói o Min-Heap (Build-Heap) de baixo para cima
        for (int i = tamanho / 2 - 1; i >= 0; i--) {
            heapify(i);
        }

        // Passo 2: Extrai a raiz sucessivamente para o final do arranjo
        for (int i = tamanho - 1; i >= 0; i--) {
            trocar(0, i);
            tamanho = i; // Isola o menor elemento já posicionado no final
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

    cout << "=== DEMONSTRACAO DA MIN-HEAP ===" << endl;
    cout << "Vetor original a ser inserido: ";
    for (int num : arranjo) cout << num << " ";
    cout << "\n\n";

    // 1. Cria a Min-Heap e insere os elementos
    MinHeapBinaria min_heap(arranjo.size());
    for (int num : arranjo) {
        min_heap.inserir(num);
    }

    cout << "Arranjo interno estruturado como Min-Heap: ";
    min_heap.imprimir();

    // 2. Consulta da raiz
    cout << "Menor elemento atual (raiz): " << min_heap.obter_raiz() << endl;

    // 3. Remocao do elemento de menor prioridade
    cout << "Removendo o menor elemento: " << min_heap.remover_raiz() << endl;
    cout << "Min-Heap apos a remocao: ";
    min_heap.imprimir();

    // 4. Teste de ordenacao completa via Heapsort
    // Reinserindo o elemento para restaurar o vetor completo
    min_heap.inserir(1);
    cout << "\nExecutando Heapsort (ordem decrescente)..." << endl;
    min_heap.heap_sort();
    cout << "Vetor totalmente ordenado: ";
    min_heap.imprimir(arranjo.size());

    return 0;
}
