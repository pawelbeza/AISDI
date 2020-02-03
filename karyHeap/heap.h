#include <iostream>
#include <vector>

template<int k, typename KeyType, typename ValueType>
class Heapk
{
public:
    using KeyValueType = std::pair<KeyType, ValueType>;

    Heapk() = default;
    ~Heapk() = default;

    bool empty() const noexcept {
        return !heap.size();
    }
    void insert(KeyType const & key, ValueType const & value) {
        KeyValueType pair = std::make_pair(key, value);
        if (!heap.size()) {
            heap.push_back(pair);
            return;
        }

        heap.push_back(pair);
        restoreUp(heap.size() - 1);
    }

    void restoreUp(int index) {
        int parent = (index - 1) / k;
        while (parent >= 0) {
            if (heap[parent].first > heap[index].first) {
                std::swap(heap[parent], heap[index]);
                index = parent;
                parent = (index - 1) / k;
            }
            else
            {
                break;
            }
            
        }
    }

    void restoreDown(int index) {
        while (k * index + 1 < heap.size()) {
            int max_index = index;
            for (int i=k*index + 1; i < heap.size() && i <= k*index + k; i++)
                if (heap[i].first < heap[max_index].first)
                    max_index = i;
            if (max_index != index) {
                std::swap(heap[max_index], heap[index]);
                index = max_index;
            }
            else
            {
                break;
            }
        }
    }

    void insert(KeyValueType const & key_value) {
        insert(key_value.first, key_value.second);
    }

    KeyValueType & peek() {
        if (!heap.size()) {
            throw std::logic_error("Heap is empty");
        }
        return heap[0];
    }

    KeyValueType pop() noexcept {
        if (!heap.size())
            return std::make_pair(KeyType(), ValueType());
        KeyValueType retpair = heap[0];
        std::swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        restoreDown(0);
        return retpair;
    }

    size_t size() const noexcept {
        return heap.size();
    }

    template<typename StreamType>
    void print(StreamType& stream) const {
        int rowSize = 1;
        for (int i=0; i < heap.size(); i++) {
            if (rowSize == i) {
                stream << '\n';
                rowSize = rowSize * k + 1;
            }
            stream << "|" <<  heap[i].first << "," << heap[i].second << "|  ";
        }
        stream << std::endl;
    }
private:
    std::vector<KeyValueType> heap;
};