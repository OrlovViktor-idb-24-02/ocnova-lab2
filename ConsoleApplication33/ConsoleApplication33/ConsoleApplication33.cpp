//#include "pch.h"
//using namespace System;
//using namespace System::Collections::Generic;
//using namespace System::IO;
//
//public ref class Shape abstract {
//public:
//    virtual double Area() abstract;
//    virtual double Perimeter() abstract;
//    virtual void Print() {
//        Console::WriteLine(ToString());
//    }
//    virtual String^ ToString() override {
//        return String::Format("Area={0:F2}, Perimeter={1:F2}", Area(), Perimeter());
//    }
//    virtual String^ Serialize() abstract;
//    static Shape^ Deserialize(String^ line);
//};
//
//public ref class Circle sealed : public Shape {
//    double r;
//public:
//    Circle(double r) {
//        {
//            if (r <= 0) throw gcnew ArgumentOutOfRangeException("r");
//            this->r = r;
//        }
//    }
//    virtual double Area() override { return Math::PI * r * r; }
//    virtual double Perimeter() override { return 2 * Math::PI * r; }
//    virtual String^ ToString() override {
//        return String::Format("Circle(r={0:F2}): {1}", r, Shape::ToString());
//    }
//    virtual String^ Serialize() override {
//        return String::Format("Circle;{0}", r);
//    }
//};
//
//public ref class Rectangle sealed : public Shape {
//    double w, h;
//public:
//    Rectangle(double w, double h) {
//        {
//            if (w <= 0 || h <= 0)
//                throw gcnew ArgumentOutOfRangeException("w,h");
//            this->w = w;
//            this->h = h;
//        }
//    }
//    virtual double Area() override { return w * h; }
//    virtual double Perimeter() override { return 2 * (w + h); }
//    virtual String^ ToString() override {
//        return String::Format("Rectangle({0:F2}x{1:F2}): {2}", w, h, Shape::ToString());
//    }
//    virtual String^ Serialize() override {
//        return String::Format("Rectangle;{0};{1}", w, h);
//    }
//};
//
//public ref class Triangle sealed : public Shape {
//    double a, b, c;
//public:
//    Triangle(double a, double b, double c) {
//        if (a <= 0 || b <= 0 || c <= 0)
//            throw gcnew ArgumentOutOfRangeException("sides must be positive");
//        this->a = a;
//        this->b = b;
//        this->c = c;
//    }
//    virtual double Perimeter() override { return a + b + c; }
//    virtual double Area() override {
//        double p = Perimeter() / 2.0;
//        return Math::Sqrt(p * (p - a) * (p - b) * (p - c));
//    }
//    virtual String^ ToString() override {
//        return String::Format("Triangle({0:F2},{1:F2},{2:F2}): {3}", a, b, c, Shape::ToString());
//    }
//    virtual String^ Serialize() override {
//        return String::Format("Triangle;{0};{1};{2}", a, b, c);
//    }
//};
//
//Shape^ Shape::Deserialize(String^ line) {
//    array<String^>^ parts = line->Split(';');
//    String^ type = parts[0];
//
//    if (type == "Circle") {
//        return gcnew Circle(Double::Parse(parts[1]));
//    }
//    else if (type == "Rectangle") {
//        return gcnew Rectangle(Double::Parse(parts[1]), Double::Parse(parts[2]));
//    }
//    else if (type == "Triangle") {
//        return gcnew Triangle(Double::Parse(parts[1]), Double::Parse(parts[2]), Double::Parse(parts[3]));
//    }
//    return nullptr;
//}
//
//int main() {
//    List<Shape^>^ shapes = gcnew List<Shape^>();
//    shapes->Add(gcnew Circle(5.0));
//    shapes->Add(gcnew Rectangle(4.0, 6.0));
//    shapes->Add(gcnew Triangle(3.0, 4.0, 5.0));
//    shapes->Add(gcnew Circle(2.0));
//    shapes->Add(gcnew Rectangle(3.0, 3.0));
//
//    Console::WriteLine("=== ALL SHAPES ===");
//    double totalArea = 0, totalPerimeter = 0;
//    for each(Shape ^ shape in shapes) {
//        shape->Print();
//        totalArea += shape->Area();
//        totalPerimeter += shape->Perimeter();
//    }
//
//    Console::WriteLine("\n=== SUMM ===");
//    Console::WriteLine("Total Area: {0:F2}", totalArea);
//    Console::WriteLine("Total Perimeter: {0:F2}", totalPerimeter);
//
//    Console::WriteLine("\n=== FIND TRIANGLES ===");
//    int triangleCount = 0;
//    double triangleAreaSum = 0;
//    for each(Shape ^ shape in shapes) {
//        Triangle^ triangle = dynamic_cast<Triangle^>(shape);
//        if (triangle != nullptr) {
//            triangleCount++;
//            triangleAreaSum += triangle->Area();
//        }
//    }
//    if (triangleCount > 0) {
//        Console::WriteLine("Triangles found: {0}", triangleCount);
//        Console::WriteLine("Average triangle area: {0:F2}", triangleAreaSum / triangleCount);
//    }
//
//    Console::WriteLine("\n=== SERIALIZATION ===");
//    StreamWriter^ writer = gcnew StreamWriter("shapes.txt");
//    for each(Shape ^ shape in shapes) {
//        writer->WriteLine(shape->Serialize());
//    }
//    writer->Close();
//    Console::WriteLine("Saved to shapes.txt");
//
//    Console::WriteLine("\n=== DESERIALIZATION ===");
//    StreamReader^ reader = gcnew StreamReader("shapes.txt");
//    String^ line;
//    while ((line = reader->ReadLine()) != nullptr) {
//        try {
//            Shape^ shape = Shape::Deserialize(line);
//            Console::WriteLine("Loaded: {0}", shape);
//        }
//        catch (Exception^ e) {
//            Console::WriteLine("Error: {0}", e->Message);
//        }
//    }
//    reader->Close();
//
//    return 0;
//}
//



#include "pch.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

public ref class Payment abstract {
public:
    virtual double CalculateFee() abstract;
    virtual double GetAmount() abstract;
    virtual double GetTotal() {
        return GetAmount() + CalculateFee();
    }
    virtual void Print() {
        Console::WriteLine(ToString());
    }
    virtual String^ ToString() override {
        return String::Format("Amount: {0:F2}, Fee: {1:F2}, Total: {2:F2}",
            GetAmount(), CalculateFee(), GetTotal());
    }
    virtual String^ Serialize() abstract;
    static Payment^ Deserialize(String^ line);
};

// Наличный платеж
public ref class CashPayment sealed : public Payment {
    double amount;
public:
    CashPayment(double amount) {
        if (amount <= 0) throw gcnew ArgumentOutOfRangeException("amount");
        this->amount = amount;
    }
    virtual double CalculateFee() override {
        return 0;
    }
    virtual double GetAmount() override {
        return amount;
    }
    virtual String^ ToString() override {
        return String::Format("Cash Payment: {0}", Payment::ToString());
    }
    virtual String^ Serialize() override {
        return String::Format("Cash;{0}", amount);
    }
};

// Карточный платеж - перегруженные конструкторы вместо аргументов по умолчанию
public ref class CardPayment sealed : public Payment {
    double amount;
    double feePercent;
public:
    // Конструктор с комиссией
    CardPayment(double amount, double feePercent) {
        if (amount <= 0) throw gcnew ArgumentOutOfRangeException("amount");
        if (feePercent < 0) throw gcnew ArgumentOutOfRangeException("feePercent");
        this->amount = amount;
        this->feePercent = feePercent;
    }
    // Конструктор с комиссией по умолчанию (2.0%)
    CardPayment(double amount) : CardPayment(amount, 2.0) {}

    virtual double CalculateFee() override {
        return amount * feePercent / 100.0;
    }
    virtual double GetAmount() override {
        return amount;
    }
    virtual String^ ToString() override {
        return String::Format("Card Payment (Fee: {0:F1}%): {1}", feePercent, Payment::ToString());
    }
    virtual String^ Serialize() override {
        return String::Format("Card;{0};{1}", amount, feePercent);
    }
};

// Онлайн платеж - перегруженные конструкторы
public ref class OnlinePayment sealed : public Payment {
    double amount;
    double fixedFee;
public:
    // Конструктор с фиксированной комиссией
    OnlinePayment(double amount, double fixedFee) {
        if (amount <= 0) throw gcnew ArgumentOutOfRangeException("amount");
        if (fixedFee < 0) throw gcnew ArgumentOutOfRangeException("fixedFee");
        this->amount = amount;
        this->fixedFee = fixedFee;
    }
    // Конструктор с комиссией по умолчанию (5.0)
    OnlinePayment(double amount) : OnlinePayment(amount, 5.0) {}

    virtual double CalculateFee() override {
        return fixedFee;
    }
    virtual double GetAmount() override {
        return amount;
    }
    virtual String^ ToString() override {
        return String::Format("Online Payment (Fixed fee: {0:F2}): {1}", fixedFee, Payment::ToString());
    }
    virtual String^ Serialize() override {
        return String::Format("Online;{0};{1}", amount, fixedFee);
    }
};

// Реализация десериализации
Payment^ Payment::Deserialize(String^ line) {
    array<String^>^ parts = line->Split(';');
    String^ type = parts[0];

    if (type == "Cash") {
        return gcnew CashPayment(Double::Parse(parts[1]));
    }
    else if (type == "Card") {
        if (parts->Length > 2) {
            return gcnew CardPayment(Double::Parse(parts[1]), Double::Parse(parts[2]));
        }
        else {
            return gcnew CardPayment(Double::Parse(parts[1])); // Используем конструктор с одним параметром
        }
    }
    else if (type == "Online") {
        if (parts->Length > 2) {
            return gcnew OnlinePayment(Double::Parse(parts[1]), Double::Parse(parts[2]));
        }
        else {
            return gcnew OnlinePayment(Double::Parse(parts[1])); // Используем конструктор с одним параметром
        }
    }
    return nullptr;
}

int main() {
    // Создаем реестр платежей - теперь используем правильные конструкторы
    List<Payment^>^ payments = gcnew List<Payment^>();
    payments->Add(gcnew CashPayment(1000.0));
    payments->Add(gcnew CardPayment(500.0, 1.5));  // Явно указываем комиссию
    payments->Add(gcnew OnlinePayment(200.0, 3.0)); // Явно указываем комиссию
    payments->Add(gcnew CashPayment(750.0));
    payments->Add(gcnew CardPayment(300.0));        // Используем комиссию по умолчанию
    payments->Add(gcnew OnlinePayment(1500.0));     // Используем комиссию по умолчанию

    // Детальный отчет по платежам
    Console::WriteLine("=== DETAILED PAYMENT REPORT ===");
    double totalAmount = 0, totalFees = 0, totalOverall = 0;
    for each (Payment ^ payment in payments) {
        payment->Print();
        totalAmount += payment->GetAmount();
        totalFees += payment->CalculateFee();
        totalOverall += payment->GetTotal();
    }

    // Суммарная информация
    Console::WriteLine("\n=== SUMMARY ===");
    Console::WriteLine("Total Amount: {0:F2}", totalAmount);
    Console::WriteLine("Total Fees: {0:F2}", totalFees);
    Console::WriteLine("Total Overall: {0:F2}", totalOverall);
    Console::WriteLine("Number of payments: {0}", payments->Count);

    // Агрегаты по типам платежей
    Console::WriteLine("\n=== AGGREGATES BY PAYMENT TYPE ===");
    int cashCount = 0, cardCount = 0, onlineCount = 0;
    double cashAmount = 0, cardAmount = 0, onlineAmount = 0;
    double cashFees = 0, cardFees = 0, onlineFees = 0;

    for each (Payment ^ payment in payments) {
        CashPayment^ cash = dynamic_cast<CashPayment^>(payment);
        CardPayment^ card = dynamic_cast<CardPayment^>(payment);
        OnlinePayment^ online = dynamic_cast<OnlinePayment^>(payment);

        if (cash != nullptr) {
            cashCount++;
            cashAmount += cash->GetAmount();
            cashFees += cash->CalculateFee();
        }
        else if (card != nullptr) {
            cardCount++;
            cardAmount += card->GetAmount();
            cardFees += card->CalculateFee();
        }
        else if (online != nullptr) {
            onlineCount++;
            onlineAmount += online->GetAmount();
            onlineFees += online->CalculateFee();
        }
    }

    // Вывод агрегатов
    if (cashCount > 0) {
        Console::WriteLine("Cash Payments: {0} transactions, Amount: {1:F2}, Fees: {2:F2}",
            cashCount, cashAmount, cashFees);
    }
    if (cardCount > 0) {
        Console::WriteLine("Card Payments: {0} transactions, Amount: {1:F2}, Fees: {2:F2}",
            cardCount, cardAmount, cardFees);
    }
    if (onlineCount > 0) {
        Console::WriteLine("Online Payments: {0} transactions, Amount: {1:F2}, Fees: {2:F2}",
            onlineCount, onlineAmount, onlineFees);
    }

    // Сериализация
    Console::WriteLine("\n=== SERIALIZATION ===");
    StreamWriter^ writer = gcnew StreamWriter("payments.txt");
    for each (Payment ^ payment in payments) {
        writer->WriteLine(payment->Serialize());
    }
    writer->Close();
    Console::WriteLine("Saved to payments.txt");

    // Десериализация
    Console::WriteLine("\n=== DESERIALIZATION ===");
    StreamReader^ reader = gcnew StreamReader("payments.txt");
    String^ line;
    while ((line = reader->ReadLine()) != nullptr) {
        try {
            Payment^ payment = Payment::Deserialize(line);
            if (payment != nullptr) {
                Console::WriteLine("Loaded: {0}", payment);
            }
        }
        catch (Exception^ e) {
            Console::WriteLine("Error: {0}", e->Message);
        }
    }
    reader->Close();

    // Демонстрация расчета комиссии для каждого типа
    Console::WriteLine("\n=== FEE CALCULATION DEMO ===");
    Payment^ demo1 = gcnew CashPayment(1000.0);
    Payment^ demo2 = gcnew CardPayment(1000.0, 2.0);  // Явно указываем комиссию
    Payment^ demo3 = gcnew OnlinePayment(1000.0, 10.0); // Явно указываем комиссию

    demo1->Print();
    demo2->Print();
    demo3->Print();

    return 0;
}