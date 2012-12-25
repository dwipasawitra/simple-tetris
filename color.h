class color
{
private:
    int red;
    int green;
    int blue;
public:
    int toInt();
    color(int red, int green, int blue);
    static color getNew16color();
};
