#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <functional>  // std::less

template<typename ElementType, typename Compare = std::less<ElementType>>
class OrderedVector {
public:
    OrderedVector(unsigned int maxLen, Compare cmp = Compare{})
        : m_maxLen(maxLen), m_data(std::make_unique<ElementType[]>(m_maxLen)), m_cmp(cmp) { }

    OrderedVector(const OrderedVector&) = delete;
    OrderedVector& operator=(const OrderedVector&) = delete;

    bool add(ElementType value) {
        if (m_len >= m_maxLen) {
            return false;
        }
        //место индеекса
        unsigned int insertIndex = 0;
        while (insertIndex < m_len && m_cmp(m_data[insertIndex], value)) {
            insertIndex++;
        }
        //подвигаю масивчик
        for (unsigned int i = m_len; i > insertIndex; --i) {
            m_data[i] = m_data[i - 1];
        }

        // Вставка
        m_data[insertIndex] = value;
        ++m_len;
        return true;
    }

    ElementType& at(unsigned int n) {
        if (n >= m_len) {
            throw std::out_of_range("too big");
        }
        return m_data[n];
    }

    ElementType& operator[](unsigned int n) {
        return at(n);
    }

    void print() const {
        for (unsigned int i = 0; i < m_len; ++i)
            std::cout << m_data[i] << " ";
        std::cout << '\n';
    }

private:
    unsigned int m_len = 0;
    unsigned int m_maxLen;
    Compare m_cmp;
    std::unique_ptr<ElementType[]> m_data;
};
