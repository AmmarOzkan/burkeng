# burkeng
Burkeng oyun motoru

Temel Başlangıç:
Öncelikle SFML kütüphanesinden bir sf::RenderWindow oluşturmalısınız. Bu sizin ana pencereniz olacak.
Şuradaki gibi tanımlanabilir:
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pencere Başlığı");

Ardından Burkeng kütüphanesinden setWindow(); fonksiyonunu kullanarak hızlıca oyun için programı hazırlayabilirsiniz.
Şuradaki gibi kullanılabilir:
setWindow(window,60);

Ardından oyunumuzun ana döngüsünü oluşturmamız gerekecek.
SFML'de nasıl kullanıyorsak o şekilde kullanalım.

while(window.isOpen()){
	sf::Event event;
	while(window.pollEvent(event)){
		//Event olayları
	}
	//Çizim ve döngü için gereken şeyler
}


Ardından texture yükleyip o texture ile obje oluşturup bir fizik objesine atayalım.
Bunu şu şekilde yapabiliriz:
Texturee değişkeni tanımlayıp bunu setTexturee() fonksiyonu ile dosyadan atarız,
sonra atanmış texture ile bir gameObject oluştururuz ve bir kamera verisi oluşturup ona atarız,
sonra oluşturduğumuz gameObject'i bir physicsObject'e atarız.

Bunu döngüden önce yapmalıyız:

TEXTURE YÜKLEME İŞLEMİ:
Texturee karakterTexture;
setTexturee(&karakterTexture, 820,1181,"KarakterTexture'ı","res/imgs/character_test.jpg");

setTexturee fonksiyonu burada 820x1181 çözünürlükte character_test.jpg adlı dosya üzerinde çalışmıştır.
Ve texture yüklendimi yüklenmedimi belirtmek için komut satırına:
KarakterTexture yüklenme durumu (yüklenme durumu bool türünden)

GAMEOBJECT OLUŞTURMA İŞLEMİ:

gameObject karakterObjesi(karakterTexture,WIDTH/2,HEIGHT/2,1,1,false,&window,&camera);

karakterTexture'ımızı karakterObjesi texture'ına atadık ve pozisyonunu WIDTH/2,HEIGHT/2 'a ayarladık.
scale verilerini 1,1 girdik ve math kısmına false girdik.
Yani texture x tarafından *1 büyütülecek ve y tarafından *1 büyütülecek.
Eğer math kısmına true girseydik objemiz 1 pixele 1 pixel olacaktı.

Ardından pencere objemizin adresini &window yazarak belirledik ve sonra camera objemizin adresini oraya yazdık (&camera)

Kamera objesinin tanımı oldukça basittir:
valueXY camera = {0,0};
valueXY bir bakıma oyun motorlarında sıkça karşılaşılan Vector2 değişken tipidir.
camera'nın pozisyonunu 0,0 olarak belirledik.

PHYSICSOBJECT OLUŞTURMA:
physicsObject karakter(&karakterObjesi, false, 0.0, "OYUNCAK");

karakterObjesi'ni physicsObject'in gameObject bölümüne atadık.
Fizik olaylarının gerçekleşip gerçekleşmeyeceğini false olarak belirttik(yerçekimi vb şeyler gerçekleşmeyecek)
Yerçekimini 0.0 ayarladık (gerek yok zaten)
Komut satırına oluşturulduğu zaman OYUNCAK oluşturuldu gibi bir mesaj yazılacak.


Obje oluşturma kodlarımız bitti şimdi onu ekrana çizdirelim.
Öncelikle şundan bahsetmemiz gerekir:
Düzen için tavsiye edilen while döngüsü pozisyonları


while(){
	//EVENT OLAYLARI
	//KONTROL OLAYLARI
	//ÇARPIŞMA OLAYLARI
	//FIZIK OLAYLARI
	//ÇİZİM OLAYLARI
}

Objemizi çizdirmek için tek yapmamız gereken şey ÇİZİM OLAYLARI kısmına karakter.draw(); yazmak.

NOT: 
SFML'de pencerenin olmazsa olmaz komutu display()'dur. Unutmayalım

İşte objemiz çarpışmayı kontrol etmeye, yönetmeye hazır!

Objemiz çokmu büyük geldi yada çokmu küçük geldi?
Objemizin dikey ve yatay uzunluğunu gameObject oluşturma fonksiyonunda belirtebiliriz.
1,1,false, kısmını hatırlamamız gerek bu kısımda.
Burada 0.'lı değerler verirsek küçülür 1'den büyük değerler verirsek büyür fakat biz belli bir büyüklüğe
ulaşmasını istiyoruz.
O zaman buraya false olan kısma true yazmak gerekiyor.
800,600,true yazarsak objemiz 800 600 büyüklüğünde olacaktır.
Ben burada 200,200 kullanacağım.
gameObject karakterObjesi(karakterTexture,WIDTH/2,HEIGHT/2,200,200,true,&window,&camera);


NOT: gameObject'de physics object gibi draw() fonksiyonuyla çizilebilir physicsObject olmasının tek farkı kontrollü bir şekilde
haraket sistemidir.


PHYSICSOBJECT'LERDE HARAKET:
physicsObject'imizi güvenli bir şekilde haraket ettirmek istiyorsak addX veya addY fonksiyonunu kullanacağız.
Bu fonksiyonların işlevi:
parametreleri genellemek gerekirse:
düzlemde eklenecek olan pozisyon, kaç birimde bir kontrol edileceği, çarpışma tagı
İlk parametre kaç birim sağa sola yukarı veya aşağı gideceğimizi belirler.
İkince parametre kaç birimde bir kontrol edileceğini belirtir.
Üçüncüsü ise hangi çarpışma tagında ilerlemenin duracağını belirtir.

Eğer objemize kontrol edilecek bir trigger değişkeni eklemek istiyorsak physicsObject'in şu fonksiyonunu kullanmalıyız:
addControl(urTrigger, id);
urTrigger, trigger değişkeninin adresidir. Eğer bir physicsObject'teki triggerı almak istiyorsak şu fonksiyonu kullanmalıyız:
getTrigger();
Ve eklenecek objenin trigger'ının en son durumda kullanılmasını istediğimiz için şu fonksiyonu 2. nesne üstüne kullanmalıyız:
setColliding()
yani eğer bir objeyi bir objenin kontrol edilecekleri arasına ekleyeceksek şunu yapmalıyız:
Bir objemiz karakter diğeride duvar olsun.
duvar.setColliding();
karakter.addControl(duvar.getTrigger(),"duvar");

Artık karakter.addX(10,0.1,"duvar") yazdığımızda duvar objemize çarpana kadar 10 birim gitme hedefini tamamlamaya devam edecek.

PHYSICSOBJECT'LERDE FORCE:
karkater adında bir physicsObject'imiz olsun.
karkater.forceClear() fonksiyonu force.x ve force.y'yi 0 yapacaktır.
Yani bunu force başlatıcı olarak düşünebiliriz.
karkater.addForce(x,y) fonksiyonu force'a x ve y olarak verileri ekler. Mesela zıpladığımızda y'ye -5 eklendi. Yerçekimi 3tü
ve yerçekiminden dolayı zıplamadan bir süre sonra aşağı doğru düştük. Bunun kodda yeri şu şekildir:

while döngüsü pozisyonlarında kontrol kısmında olacak kısım:

//zıplama
if(ziplama){
	karkater.addForce(0,-5.0)
}

while döngüsü pozisyonlarında fizik kısmında olacak kısım:

karkater.phyMove(0.1,"");
//0.1 birimde kontrol edilecek ve herhangi bir objeye çarptığında duracak (karkatere eklenmiş olan objeler)
YADA
karkater.phyMove(0.1,"duvar");
//0.1 birimde kontrol edilecek ve duvar idli objeye çarptığında duracak (karkatere eklenmiş olan objeler)

BUTON OLUŞTURMA:
Button değişkeni buton ile ilgili herşeyi içerir.
Oluşturum fonksiyonu
Button(ButonTexturu,"KomutSatirindaOlusturulurkenYazilacakSey",posX,posY,width,heigth,&window)

Button'lar .draw() fonksiyonu ile ekrana çizilir.

Butonların tıklanıp tıklanmadığını kontrol etmek için event için kullanılan while'ın içine şu fonksiyon yazılmalıdır:
button.control(event);
Şu şekil kullanılır:
while(window.pollEvent(event)){
	button.control(event);
}

KONTROL bölümünde tıklanıp tıklanmadığını kontrol etmek istiyorsak:
if(button.getClick()) kullanılmalıdır.

Panellerin ne işe yaradığı ve nasıl kullanıldığı eklenecek.
