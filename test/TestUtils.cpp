 #include "TestUtils.h"
 
 namespace TestUtils
 {
 
 std::function<bool(const Order& r, const Order& er)> orderComparator = [](const Order& r, const Order& er){
        return r.traderIdentifier() == er.traderIdentifier()
            && OrderType::Type(r.type()) == OrderType::Type(r.type())
            && r.price() == er.price()
            && r.quantity() == r.quantity();
    };
 }