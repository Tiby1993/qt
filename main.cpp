#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <QString>

QStringList list;
QStringList commandhex;

/*!
 *\brief parseInput
 * parseInputFile alapján tölt be egy hexdumpot List változóba.
 * Példa : parseInputFile("C:\\Users\\tibor\\Desktop\\asd.txt")
*/
void parseInput(QString inputFileName){
    QFile *file = new QFile(inputFileName);
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);
    QString line;
    QStringList line1;
    while (!in.atEnd( )) {
        line = in.readLine();
        line1= line.split(' ');
        list<<line1;
        list.removeAll("");
        list.removeAll("\n");
    }
    file->close( );
}
/*!
 * \brief clear
 * Kiüríti a hexdump változó tartalmát.
 */
void clear(){
    list.clear();
}

/*!
 *\brief hextodec
 *  hexából decimálisravált
 */
int hextodec(QString hex){
    bool ok;
    return hex.toInt(&ok, 16);
}
//hexából binárisbavált
int hextobin(QString hex){
    bool ok;
    int dec = hex.toInt(&ok, 16);
    return QString::number(dec, 2).toInt(&ok,10);
}

/*! executeCommand: hexa kódjuk alapján parancsokat hajt végre.
  * commandCodeInHex - a parancs hexakódja
  * param1 - a parancs 1. paramétere. (ha va)
  * param2 - a parancsk 2. paramétere (ha van)
  * példa : executeCommand("CMP",í "B4" ,"4C")
 */
/*
void executeCommand(QString commandCodeInHex, QString param1=0, QString param2=0){
//parancsok hexában az indexek alapján ugrik a switch a case ágba.
commandhex << "32" << "3D" << "51" << "6C" << "63" << "9F" << "F9" << "AA" << "C2" << "CD" << "07" << "08" << "AF" << "A0" << "E2" << "9A" << "95" << "B9" << "B6" << "8C" << "F3" << "55" << "11" << "24" << "00";
    switch(commandhex.indexOf(commandCodeInHex)){
        case 0:
            list[hextodec(param1)]="00";
        break;

        case 1:
         list[hextodec(param1)]="11";
        break;

        case 2:{
        QString value = QString::number(hextobin(list.at(hextodec(param1))));
        QString value2;
        for(int i = 0; i< value.size();i++){
            value2[i]=value[value.size()-i];
        }
        //BIN TO HEX HIÁNYZIK
        list[hextodec(param1)]= value2;
        break;
}
        case 3:
        list[hextodec(param2)]= list.at(hextodec(param1));
        break;

        case 4:
        list[hextodec(param2)] = param2;
        break;

        case 5:
        QString value=QString::number(hextobin(list.at(hextodec(param1))));
        QString value2 = value.insert(0, value.right(param2));
        list[hextodec(param1)] = value.remove((value.size()-param2), value.size());
        break;
        //!!!!!!!!!!!!!!!
        case 6:
        QString value=QString::number(hextobin(list.at(hextodec(param1))));
        QString value2 = value.append(value.right(param2));
        list[hextodec(param1)] = value.remove((0, (param2-1));
        break;

        case 7:
{
        QString temporary =list.at(hextodec(param1));
                list[hextodec(param1)]=list.at(hextodec(param2));
                list[hextodec(param2)]=temporary;
        break;
}
        case 8:
         list[hextodec(param1)]++;
        break;

        case 9:
            list[hextodec(param1)]--;
        break;

        case 10:
        list[hextodec(param1)]=list.at(hextodec(param1))+param2;
        break;

        case 11:
        list[hextodec(param1)]=list.at(hextodec(param1))-param2;
        break;

        case 12:
        //command INV
        break;

        case 13:
        //command ABS
        break;

        case 14:{
        //NOT
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2;
        for(int i=0;i < value.size();i++){
            if(value.at(i)=='1'){
                value2[i]='0';
            }
            else{
                value2[i]='1';
            }
        }
        list[hextodec(param1)] = value2;
        break;
}
        case 15:
        //san
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2=QString::number(hextobin( list.at(hextodec(param2))));
        QString value3;
        for(int i=0;i < value.size();i++){
            if(value.at(i)== value2.at(i)){
                value3[i]='1';
            }
            else{
                value3[i]='0';
            }
        }
        list[hextodec(param1)] = value3;
        //BIN TO HEX HIÁNYZIK
        break;

        case 16:
        //sor
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2=QString::number(hextobin( list.at(hextodec(param2))));
        QString value3;

        for(int i=0;i<= value.size();i++){
            if(value.at(i)=="1" || value2.at(i)=="1"){
                value3[i]='1';
            }
            else{
                value3[i]='0';
            }
        }
        list[hextodec(param1)] = value3;
        //BIN TO HEX HIÁNYZIK
        break;

        case 17:
        //NAN
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2=QString::number(hextobin( list.at(hextodec(param2))));
        QString value3;

        for(int i=0;i<= value.size();i++){
            if(value.at(i)=="0" && value2.at(i)=="0"){
                value3[i]='1';
            }
            else{
                value3[i]='0';
            }
        }
        list[hextodec(param1)] = value3;
        //BIN TO HEX HIÁNYZIK
        break;

        case 18:
        //NOR
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2=QString::number(hextobin( list.at(hextodec(param2))));
        QString value3;

        for(int i=0;i<= value.size();i++){
            if(value.at(i)=="1" && value2.at(i)=="1"){
                value3[i]='0';
            }
            else{
                value3[i]='1';
            }
        }
        //BIN TO HEX HIÁNYZIK
        list[hextodec(param1)] = value3;
        break;

        case 19:
        //XOR
        QString value=QString::number(hextobin( list.at(hextodec(param1))));
        QString value2=QString::number(hextobin( list.at(hextodec(param2))));
        QString value3;

        for(int i=0;i<= value.size();i++){
            if(value.at(i)== value2.at(i)){
                value3[i]='0';
            }
            else{
                value3[i]='1';
            }
        }
        list[hextodec(param1)] = value3;
        //BIN TO HEX HIÁNYZIK
        break;

        case 20:
        //'REP' máshol lesz implamentálva
        break;

        case 21:
        //máshol lesz implamentálva
        break;

        case 22:
        //NOP, nem hajt végre semmit
        break;

        case 23:
        list.at(hextodec(param1))+=list.at(hextodec(param2));
        list.at(hextodec(param2))=list.at(hextodec(param1));
        break;

        case 24:
        //command
        break;
    }
}*/

/*!
 * \brief getMemory
 * \return hexdump
 */
QStringList getMemory(){
    return list;
}

/*!
 * \brief getSourceCode
 * Gépi kódról fordít Assemblyre.
 * \return
 */
QStringList getSourceCode(){
    QStringList code;
    for(int i=4; list.at(i) != "00"; i++ ){
        commandhex << "32" << "3D" << "51" << "6C" << "63" << "9F" << "F9" << "AA" << "C2" << "CD" << "07" << "08" << "AF" << "A0" << "E2" << "9A" << "95" << "B9" << "B6" << "8C" << "F3" << "55" << "11" << "24";
            switch(commandhex.indexOf(list.at(i))){
            case 0:
                code.append("RST ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 1:
                code.append("FLL ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 2:
                code.append("REV ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 3:
                code.append("CPY ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 4:
                code.append("MOV ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 5:
                code.append("RTR ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 6:
                code.append("RTL ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 7:
                code.append("SWP ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 8:
                code.append("INC ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 9:
                code.append("DEC ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 10:
                code.append("ADD ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 11:
                code.append("SUB ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 12:
                code.append("INV ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 13:
                code.append("ABS ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 14:
                code.append("NOT ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 15:
                code.append("SAN ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 16:
                code.append("SOR ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 17:
                code.append("NAN ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 18:
                code.append("NOR ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 19:
                code.append("XOR ");
                i++;
                code.append(list.at(i));
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 20:
                code.append("REP ");
                i++;
                code.append(list.at(i));
                code << "\n";
            break;
            case 21:
                code.append("NEX ");
                code << "\n";
            break;
            case 22:
                code.append("NOP ");
                code << "\n";
            break;
            case 23:
                code.append("CMP ");
                code << "\n";
            break;
            }
    }
    code << "END";
    return code;
}
/*!
 * \brief writeToFile
 * A hexdumpot és az assembly kódot menti ki az output.txt állományba.
 */
void writeToFile(){
    QFile *file = new QFile("output.txt");
    file->open(QIODevice::WriteOnly);
    QTextStream out(file);
     for (int i = 0; i < list.size(); ++i){
            if(i%17 == 0 && i> 0){
                out << "\n";
            }
        out << list.at(i) << " ";
     }
     out << "\n" << "--------" <<"\n" << "PROGRAM" << "\n" << "--------"<< "\n";

     for (int i = 0; i < getSourceCode().size(); ++i){

     out << getSourceCode().at(i);

     }
    file->close( );
}

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);


    return a.exec();
}
