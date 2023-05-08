#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
enum ItemType {Antidote=0, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV};

class BaseItem;
class Events;
class BaseKnight;
class ArmyKnights;
class BaseOpponent;
class BaseBag;
//class BaseItem;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag * bag;
    KnightType knightType;
    bool Cursed;

public:
    bool decreased;
    void fighting(BaseOpponent * yeuquai);
    friend class ArmyKnights;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    
    // ~BaseKnight(){  ẩn đúng k, hiểu ý đó 
        
    //     delete []bag;//loi ngay day sao gio, hmm người ta kêu là không cần ư? đọc kỹ lại k hiểu :<, :)) thấy đại ý là không cần, chắc vậy
    // }
    
    //show
    KnightType showKnight();
    int showPhoenixI();
    int showAnti();
    int showLevel();
    int showHP();
    int showMaxhp();
    int showGil();
    BaseBag* showBag();
    bool showCursed();
    
    // //Update
    void updateAntidote(int new_anti);
    void updatePhoenixDown(int new_phoenix);
    void updateHP(int new_hp);
    void updateGil(int new_gil);
    void updateCursed(bool s);
    void updateLevel(int l);
};

class BaseItem {
public:
    BaseItem * next;
    ItemType loaiItem;// tim nay ha :)) u thay roi, dang coi
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    
    ~BaseItem(){
        delete next; //nma này đủ r pk? đúng rồi
    }
};

////Mot loat mon do/////
class PhoenixdownI: public BaseItem{
    public:
    PhoenixdownI(){
        loaiItem=PhoenixI;   //oke ma pk? um t thay on
        this->next=nullptr;
    }
    bool canUse (BaseKnight *);
    void use (BaseKnight * knight);
};

class PhoenixdownII: public BaseItem{
    public:
    PhoenixdownII(){
        loaiItem=PhoenixII;
        this->next=nullptr;
    }
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixdownIII: public BaseItem{
    public:
    PhoenixdownIII(){
        loaiItem=PhoenixIII;
        this->next=nullptr;
    }
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixdownIV: public BaseItem{
    public:
    PhoenixdownIV(){
        loaiItem=PhoenixIV;
        this->next=nullptr;
    }
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};

class Anti_dote: public BaseItem{
    public:
    Anti_dote(){
        loaiItem=Antidote;
    }
    bool canUse (BaseKnight * knight);
    void use (BaseKnight * knight);
};
///////////////////////

class BaseBag { 
public:
    BaseItem * head;
    BaseKnight * belongtoK;
    int maxItem[4]={-1,16,14,19};
    int currentItem;
    
    void deleteBag(BaseItem * p)
    {
        if(p->next!=nullptr)
        return deleteBag(p->next);
        else return; 
        delete p;
    }
    
    ~BaseBag(){
        deleteBag(head);// muốn thử cách của em không?  douzo
        // BaseItem * node1 = head;
        // BaseItem * node2;
        // while(node1!==nullptr)
        // {
        //     node2=node1;
        //     node1=node1->next;
        //     delete node2;
        // }
    }
    
    
    BaseBag(BaseKnight * hiepsimangtui, int pI, int anti){
        currentItem=0;
        this->belongtoK=hiepsimangtui;
        this->belongtoK->updatePhoenixDown(0);
        this->belongtoK->updateAntidote(0);
        while(pI>0){
            BaseItem * p=new PhoenixdownI();
            //cout<<'!'<<this->insertFirst(p)<<endl;  //tr ơi, 2 là số m cout sẵn ấy, rồi nhớ rồi :))
            if(this->insertFirst(p)) this->insert(p);
            pI--;
        }
        
        // ///nay cua Tran nha    ///chan hiep si Rong nap Antidote
        if(this->belongtoK->showKnight()!=DRAGON){
            while(anti>0){
            BaseItem * a=new Anti_dote();
            if(this->insertFirst(a)) this->insert(a); //tren day co insert first r  để t coi coi class thuốc đúng chưa cái
            anti--;
            }
        }
    }  
    
    void insert(BaseItem * additem) { //co the ghi ItemType item;
    //cout<<insertFirst(additem)<<endl;
  //cho nay ne, ma neu t xoa di, cha hieu sao k chay luon
        //cout<<"Bap"<<endl; //hả? cái nào không chạy? nè coi nha   đó nó vẫn k chạy, k thêm đồ vô cho t :<
        switch(additem->loaiItem){//để coi từ   khoan từ từ        từ, nó không vô được hàm insert  
            case PhoenixI:
                this->belongtoK->updatePhoenixDown(this->belongtoK->showPhoenixI()+1);
                break;
            case Antidote:
                this->belongtoK->updateAntidote(this->belongtoK->showAnti()+1);
                break;
            default: break;
        }
        this->currentItem++;
        additem->next=head;  //recheck Co phai cuoi link list se la null khong?
        head=additem;

}
    
    
    virtual bool insertFirst(BaseItem * item){
        if(maxItem[this->belongtoK->showKnight()]==-1) return true;
        if(currentItem+1<=maxItem[this->belongtoK->showKnight()]){
            if(item->loaiItem==PhoenixI){
                if(this->belongtoK->showPhoenixI()+1<=5) 
                    return true;
                else return false;
            }
            else if(item->loaiItem==Antidote){
                if(this->belongtoK->showAnti()+1<=5)
                    return true;
                else return false;
            }
            else {return true;}
        }
        else return false;
    };
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    virtual BaseItem * Search(BaseKnight*);
    BaseItem* showhead() {return head;};// cua tran 
    void SwapHead( BaseItem* t);
    void DeleteHead();
};

//cac tui do theo ten hiep si
//////////////////////////

class BaseOpponent{
public:
    bool isHades=false;
    int eventcode;
    int gil;                                                                     
    int  basedamage;
    int level0;
    virtual void fighting(BaseKnight * fightedK);  // ý là ở đây là hàm bình thường này, xong cái định nghĩa 
};                                                  //ảo vl bữa có ghi virtual rrr :))) thu                  


//mot loat con yeu quai dang ghet 

class MadBear: public BaseOpponent{
public:
    MadBear(int lv0) {
        eventcode=1;
        gil=100;
        basedamage=10;
        level0=lv0;
    }
    
};

class Bandit: public BaseOpponent{
public:
    Bandit(int lv0) {
        eventcode=2;
        gil=150;
        basedamage=15;
        level0=lv0;
    }
};

class LordLupin: public BaseOpponent{
public:
    LordLupin(int lv0) {
        eventcode=3;
        gil=450;
        basedamage=45;
        level0=lv0;
    }
};

class Elf: public BaseOpponent{
public:
    Elf(int lv0) {
        eventcode=4;
        gil=750;
        basedamage=75;
        level0=lv0;
    }
};

class Troll: public BaseOpponent{
public:
    Troll(int lv0) {
        eventcode=5;
        gil=800;
        basedamage=95;
        level0=lv0;
    }
};

class Tornbery: public BaseOpponent{
    public:
    Tornbery(int lv0){
        level0=lv0;
    }
    void fighting(BaseKnight* fightedK)  {
        if(fightedK->showLevel()>=this->level0 || fightedK->showKnight()==DRAGON)
            fightedK->updateLevel(fightedK->showLevel()+1);
        else{
            fightedK->updateCursed(true);
        }
        if(fightedK->showLevel()>10) fightedK->updateLevel(10);
    }
};

class Queen: public BaseOpponent{
    public:
    Queen(int lv0){
        level0=lv0;
    }
    //trên đây public nè lluoi xoa th :)))
    void fighting(BaseKnight* fightedK) {
        if(fightedK->showLevel()>=this->level0){
            fightedK->updateGil(2*fightedK->showGil());
        }
        else if (fightedK->showKnight()==PALADIN) return;
        else fightedK->updateGil((int)fightedK->showGil()/2);  //recheck !!!
    }
};

class Nina: public BaseOpponent{ // sao đây không có public? do k xai constructor
    void fighting(BaseKnight* fightedK){
        if(fightedK->showGil()>50 || fightedK->showKnight()==PALADIN){
            if(fightedK->showHP()<(int)fightedK->showHP()/3){
                if(fightedK->showKnight()!=PALADIN) fightedK->updateGil(fightedK->showGil()-50);
                fightedK->updateHP(fightedK->showHP()+(int) fightedK->showMaxhp()/5);
            }
        }
    }
};

class Durian: public BaseOpponent{
    void fighting(BaseKnight* fightedK){
        fightedK->updateHP(fightedK->showMaxhp());
    }
};

class OmegaW: public BaseOpponent{   //trong adventure cua ArmyKnight phai dung meetOmega de k gap lai no nx
    void fighting(BaseKnight* fightedK){
        if(fightedK->showLevel()==10 || fightedK->showHP()==fightedK->showMaxhp() || fightedK->showKnight()==DRAGON){
            fightedK->updateLevel(10);
            fightedK->updateGil(999);
        }
        else{
            fightedK->updateHP(0);
        }
    }
    ~OmegaW();
};

class Hades: public BaseOpponent{
    public:
    Hades(){
        isHades=true;
    }
    void fighting(BaseKnight* fightedK) {
        if(fightedK->showLevel()==10 || fightedK->showKnight()==PALADIN && fightedK->showLevel()>=8)
            return;
        else (fightedK->updateHP(0));  //check trong fight 
    }
};


// ket thuc bay yeu quai

class ArmyKnights {
protected:
    BaseKnight ** Armygroup;   //sua lai thanh double pointer !
    int armynum;
public:
    bool shield=false;
    bool spear=false;
    bool hair=false;
    bool sword=false;
    bool winHades=false;
    bool meetHades=false;
    bool meetOmega=false;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    
    bool fight(BaseOpponent * opponent);     
    
    bool adventure (Events * events);
    
    int count() const;
    
    BaseKnight * lastKnight() const;
    
    
    bool hasPaladinShield() const{
        return shield;
    };
    bool hasLancelotSpear() const{          
        return spear;
    };
    bool hasGuinevereHair() const{
        return hair;
    };
    bool hasExcaliburSword() const{
        return sword;
    };

    void printInfo() const;
    void printResult(bool win) const;
    void passGil();
    void passThing(BaseItem* vatpham);
};


class Events {  //class nay viet thang len 
protected:
int counting;
int * event;

public:
    Events(const string & file_events){
        ifstream sukien (file_events);
        if(sukien.fail()){
            cout<<"Cannot open file_events";
            terminate();
        }
        sukien>>counting;
        event=new int[counting];
        for(int i=0;i<counting;i++)
            sukien>>event[i];
    }
    
    int count() const{
        return counting;
    };
    int get(int i) const{
        return event[i];
    };
    ~Events(){
        delete[] event;
        event=nullptr;
    }
};

class KnightAdventure {   // doi chut đó đó, lúc chưa sửa đủ mà, thiếu 1 cái thì t thêm r coi như đủ 10
                         // là giờ check cái sự kiện thôi đúng không? tại nãy t hay bấm save lúc sửa á :) ultr :))
private:                 
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure()
    {
        armyKnights=nullptr;
        events=nullptr;
    };// giờ coi sự kiện ok
    ~KnightAdventure(){
        delete armyKnights;
        delete events;
    };

    void loadArmyKnights(const string &s){
        armyKnights=new ArmyKnights(s);
    };
    void loadEvents(const string &e){
        events= new Events(e);
    };
    void run(){
        
        
        
        armyKnights->printResult(armyKnights->adventure(events));   
        
        
        /////Tran
        
        //BaseOpponent * omega = new omegaW();
        
        // BaseKnight * Bap = new BaseKnight(); // cho nay co can dau ngoac hog
        // Bap=Bap->create(0,172,4,100,1,1);//de t coi cai constructor, khong can nha
        //cout<<Bap->showPhoenixI()<<endl;

        // BaseBag* Tran = new BaseBag(Bap,1,1); 
        // BaseItem* p= new PhoenixdownI();
        // Tran->insert(p);
        // cout<<Tran->toString()<<endl;
        // BaseItem* a=Tran->get(Antidote);
        // Tran->SwapHead(a);
        // cout<<Tran->toString()<<endl;
        // Tran->DeleteHead();
        // cout<<Tran->toString()<<endl;
        // BaseItem * p= Tran->showhead();
        // cout<<p<<endl;
        // while(p!=nullptr) 
        // {
        //     cout<<p->loaiItem<<endl;
        //     p=p->next;
        // }
        
        
        // BaseItem * BanhKaro= Tran->get(PhoenixII); 
    
        // if(BanhKaro!=NULL &&BanhKaro->loaiItem==Antidote) cout<<"Yeah"<<endl;
        // else cout<<"Sai roi :))"<<endl;
        
        // Bap->updateHP(0);
        // if (BanhKaro->canUse(Bap)) cout<<"oke"<<endl;
        // else cout<<"thoi hong them ha"<<endl;
        // ///////////
    };
};

#endif // __KNIGHT2_H__
