
#include <vector>
#include <boost/optional.hpp>

template<typename DataType>
class Tree
{
    private:
	    boost::optional<Tree&> current_node;
	    DataType data;
	    std::vector<Tree> tail;
    public:
	    Tree(void):current_node(*this){}
	    template<typename T>
	    void set_node(T&& _data){data = std::forward<T>(_data);}
	    void advance(std::size_t _selection = 0){current_node = current_node->tail[_selection];}
	    DataType get(void) const{return current_node->data;};
	    template<typename T>
	    void attach(T&& _tail){tail.push_back(std::forward<T>(_tail));}
	    template<typename T, typename... Us>
	    void attach(T&& _t, Us&&... _us)
	    {
		tail.push_back(std::forward<T>(_t)); 
		attach(std::forward<Us>(_us)...);
	    }
	    void reset(void){current_node = *this;}
};

#include <string>
#include <iostream>

int main()
{
    using Tree = Tree<std::string>;
    
    Tree script;
    script.set_node("Introduction");
    
    Tree t, s, u;
    t.set_node("first");
    s.set_node("second");
    u.set_node("third");
    
    Tree v, w;
    v.set_node("first-first");
    w.set_node("first-second");
    
    t.attach(v, w);
    
    script.attach(t, s, u);
    
    //Pathway1: 0->1
    std::cout << script.get() << std::endl;
    script.advance(0);
    std::cout << script.get() << std::endl;
    script.advance(1);
    std::cout << script.get() << std::endl;
    
    script.reset();
    
    //Pathway2: 0->0
    std::cout << script.get() << std::endl;
    script.advance(0);
    std::cout << script.get() << std::endl;
    script.advance(0);
    std::cout << script.get() << std::endl;
}

