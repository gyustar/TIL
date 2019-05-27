## 11. 기본 API 클래스

> 자바 API 도큐먼트

API(Application Programming Interface)는 라이브러리라고 부르기도 하는데, 프로그램 개발에 자주 사용되는 클래스 및 인터페이스의 모음을 말한다. 이 API들은 <JDK 설치경로> /jre/lib/rt.jar라는 압축 파일에 저장되어 있다.<br>
API 도큐먼트는 쉽게 API를 찾아 이용할 수 있도록 문서화한 것을 말한다. HTML 페이지로 작성되어 있기 때문에 웹 브라우저를 열고 오라클에서 제공하는 다음 URL을 방문하면 볼 수 있다.<br>
*https://docs.oracle.com/en/java/javase/12/docs/api/index.html*<br>

> java.lang과 java.util 페이지

- java.lang 패키지<br>
  자바 프로그램의 기본적인 클래스를 담고 있는 패키지이다. 그렇기 때문에 java.lang의 클래스와 인터페이스는 import 없이 사용할 수 있다. 다음은 주요 클래스들이다.
  - Object : 자바 클래스의 최상위 클래스로 사용
  - System :
    - 표준 입력 장치(키보드)로부터 데이터를 입력받을 때 사용
    - 표준 출력 장치(모니터)로 출력하기 위해 사용
    - 자바 가상 기계를 종료시킬 때 사용
    - 쓰레기 수집기를 실행 요청할 때 사용
  - Class : 클래스를 메모리로 로딩할 때 사용
  - String : 문자열을 저장하고 여러 가지 정보를 얻을 때 사용
  - StringBuffer, StringBuilder : 문자열을 저장하고 내부 문자열을 조작할 때 사용
  - Math : 수학 함수를 이용할 때 사용
  - Wrapper - Byte, Short, Character, Integer, Float, Double, Boolean. Long
    - 기본 타입의 데이터를 갖는 객체를 만들 때 사용
    - 문자열을 기본 타입으로 변환할 때 사용
    - 입력값 검사에 사용
- java.util 패키지<br>
  자바 프로그램 개발에 조미료 같은 역할을 하는 클래스를 담고 있다. 컬렉션 클래스들이 대부분이다.
  - Arrays : 배열을 조작(비교, 복사, 정렬, 찾기)할 때 사용
  - Calender : 운영체제의 날짜와 시간을 얻을 때 사용
  - Date : 날짜와 시간 정보를 저장하는 클래스
  - Objects : 객체 비교, null 여부 등을 조사할 때 사용
  - StringTokenizer : 특정 문자로 구분된 문자열을 뽑아낼 때 사용
  - Random : 난수를 얻을 때 사용

> Object 클래스

클래스를 선언할 때, extends 키워드로 다른 클래스를 상속하지 않으면 암시적으로 java.lang.Object 클래스를 상속하게 된다. 즉, 자바의 모든 클래스는 Object 클래스의 자식이거나 자손 클래스이다. Object 클래스는 필드가 없고 메소드들로만 구성되어 있다. 당연히 모든 클래스에서 사용이 가능하다. 다음은 Object의 메소드들이다.
- 객체 비교(equals())
  ```java
  public boolean equals(Object obj) {...}
  ```
  이 메소드는 두 객체가 논리적으로 동일한 객체라면 true를 리턴하고 아니면 false를 리턴한다. 문자열의 경우 번지 수가 아닌 문자열 자체를 비교한다. String 클래스가 이 메소드를 재정의 해서 번지 수가 아닌 문자열 비교로 변경했기 때문이다.<br>
  equals()메소드를 재정의할 때에는 매개값(비교 객체)이 기준 객체와 동일한 타입의 객체인지 먼저 확인해야 한다. instanceof 연산자로 먼저 확인해야 한다. 동일하다면 기준 객체 타입으로 강제 타입 변환해서 값이 동일한지 검사하면 된다.
- 객체 해시코드(hashCode())<br>
  객체 해시코드란 객체를 식별할 하나의 정수값을 말한다. hashCode() 메소드는 객체의 메모리 번지를 이용해서 해시코드를 만들어 리턴하기 때문에 객체마다 다른 값을 가진다. 논리적 동등 비교 시, 이 메소드를 오버라이딩할 필요 있는데, HashMap, HashSet, Hashtable은 다음과 같은 방법으로 두 객체가 동등한지 비교한다. 먼저 해시코드 값이 같은지를 보고 equals() 메소드로 다시 비교해서 같을 경우 동등 객체로 판단하고 true를 리턴한다. 즉, hashCode() 메소드 재정의 시 리턴하는 값을 상황에 맞게 수정해주면 된다.
- 객체 문자 정보(toString())
  ```java
  Object obj = new Object();
  System.out.println( obj.toString() );
  //실행 결과 : java.lang.Object@de6ced
  ```
  toString() 메소드는 객체의 문자 정보를 리턴한다. 문자 정보란 객체를 문자열로 표현한 값을 말한다. 기본적으로 toString() 메소드는 "클래스명@16진수해시코드"로 구성된 문자 정보를 리턴한다. 이 리턴값은 자바 애플리케이션에서는 별 값어치가 없는 정보라서, Object의 하위 클래스는 이 메소드를 재정의해서 간결하고 유익한 정보(현재 시간, 저장하고 있는 문자열 등)를 리턴하도록 한다.<br>
  *주로 사용하는 System.out.println()메소드의 경우 매개값으로 객체를 주면 객체의 toString 메소드를 호출해서 리턴값을 출력하도록 되어 있다.*
- 객체 복제(clone())<br>
  객체 복제는 원본 객체의 필드값과 동일한 값을 가지는 새로운 객체를 생성하는 것을 말한다. 원본 객체를 넘겨 작업할 경우 객체의 데이터가 훼손될 수 있기 때문에 복제된 객체를 만들어 넘기는 것이 좋다. 
  - 얕은 복제(thin clone)<br>
    얕은 복제는 단순히 필드값을 복사해서 객체를 복제한다. 필드가 기본 타입일 경우 값 복사가 일어나고, 참조 타입일 경우 객체의 번지가 복사된다.(즉 같은 번지를 참조한다.) Object의 clone() 메소드는 얕은 복제된 객체를 리턴한다. 이 메소드로 객체를 복제하려면 원본 객체는 반드시 java.lang.Cloneable 인터페이스를 구현하고 있어야 한다. 그렇지 않으면 CloneNotSupoortedException 예외가 발생한다. 복제 메소드 선언과 관계없이 명시적인 구현은 복제 허용을 의미한다.
    ```java
    try {
        Object obj = clone();//clone()메소드의 리턴 타입은 Object 이다.
    } catch(CloneNotSupportedException e) {}
    //clone()은 CloneNotSupportedException 예외 처리가 필요한 메소드이다.
    ```
  - 깊은 복제(deep clone)<br>
    얕은 복제의 경우, 참조 타입 필드는 번지만 복제되기 때문에 복제 객체에서 참조 객체를 변경하면 원본 객체도 변경된 객체를 가지게 된다. 깊은 복제는 참조하고 있는 객체도 복제한다. 깊은 복제를 하려면 clone() 메소드를 직접 재정의 해야 한다.
    ```java
    @Override
    pritected Object clone() throws CloneNotSupportedException {
        //Object의 clone()을 호출해 얕은 복사를 먼저 한다.
        Member cloned = (Member) super.clone();
        //깊은복제 대상인 참조 타입 필드(여기선 배열) 를 깊은 복제한다.
        cloned scores = Arrays.copyOf(this.scores, this.scores.length);
        //깊은복제 대상인 참조 타입 필드 (여기선 객체)를 깊은 복제한다.
        cloned.car = new Car(this.car.model);
        //깊은 복제된 원본타입 객체를 리턴
        return cloned;
    }
    ```
- 객체 소멸자(finalize())<br>
  참조하지 않는 배열이나 객체는 쓰레기 수집기가 힙 영역에서 자동으로 소멸시킨다. 이 때, 소멸 직전 객체 소멸자(finalize())가 실행된다. finalize() 메소드는 기본적으로 실행 내용이 없다. 만약 객체가 소멸되기 전에 마지막 자원을 닫고 싶거나, 중요한 데이터를 저장하고 싶다면 finalize() 메소드를 재정의하면 된다.
  ```java
  /* ex) finalize()가 실행되면 번호를 출력하게 해서
  어떤 객체가 소멸되는지 확인할 수 있게 재정의*/
  @Override
  protected void finalize() throws Throwable {
      Sustem.out.println(no + "번 객체의 finalize()가 실행됨");
  }

  System.gc(); //쓰레기 수집기 실행 요청하는 코드
  ```
  실제 실행 시, 쓰레기 수집기는 객체를 순서 없이 무작위로, 메모리 상태에 따라 일부을 소멸시킨다. 쓰레기 수집기를 실행 요청하더라도 메모리가 부족할 때 그리고 CPU가 한가할 때에 JVM에 의해 자동 실행된다. 그렇기 때문에 만약 즉시 자원을 해제하거나 데이터를 최종 저장해야 한다면, 일반 메소드에서 작성하고 명시적으로 메소드를 호출하는 것이 좋다.

> Objects 클래스

java.util.Objects 클래스는 객체 비교, 해시코드 생성, null 여부, 객체 문자열 리턴 등의 연산을 수행하는 정적 메소드들로 구성된 Object의 유틸리티 클래스이다.
- 객체 비교(compare(T a, T b, Comparator<T>c))<br>
  두 객체를 비교자 Comparator로 비교해서 int 값을 리턴한다. java.util.Comparator<T>는 제네릭 인터페이스 타입으로 두 객체를 비교하는 compare(T a, T b) 메소드가 정의되어 있다. (T는 비교할 객체 타입이다.) compare() 메소드는 a가 b보다 작으면 음수, 같으면 0, 크면 양수를 리턴하도록 구현 클래스를 만들어야 한다.
  ```java
  public interface Comparator<T> {
      int compare(T a, T b);
  }

  class 클래스이름 implements Comparator<T> {
      @Override
      public int compare(T a, T b) {
          if(a.필드 < b.필드) return -1;
          else if(a.필드 == b.필드) return 0;
          else retuen 1;
          //위 세 줄은 간단하게 return Integer.compare(a.필드,b.필드);로 대체 가능
      }
  }
  ```
- 동등 비교(equals()와 deepEquals())
  - Objects.equals(Object a, Object b)는 두 객체의 동등일 비교하는데, a와 b가 모두 null일 경우 true를 리턴한다. 하나라도 null이면 false, 둘다 null이 아닌 경우는 a.equals(b)의 결과를 리턴한다.
  - Objects.deepEquals(Object a, Object b) 역시 두 객체의 동등을 비교하는데, a와 b가 서로 다른 배열일 경우, 항목 값이 모두 같아면 true를 리턴한다. 이것은 Arrays.deepEquals(Object[] a, Object[] b)와 동일하다. 배열이 아닌 경우, equals()와 같다.
- 해시코드 생성(hash(), hashCode())
  - Objects.hash(Object...values) 메소드는 주어진 매개값들로 배열을 생성하고 Arrays.hashCode(Object[])를 호출해서 해시코드를 얻고 이 값을 리턴한다. 이 메소드는 클래스가 hashCode()를 재정의할 때 리턴값을 생성하기 위해 사용하면 좋다. 동일한 필드값을 가지는 객체는 동일한 해시코드를 가질 수 있다.
    ```java
    @Override
    public int hachCode() {
        return Objects.hash(field1, field2, field3);
    }
    ```
  - Objects.hashCode(Object o)는 매개값으로 주어진 객체의 해시코드를 리턴하기 때문에 o.hashCode()의 리턴값과 동일하다. 차이점은 매개값이 null이면 0을 리턴한다.
- 널 여부 조사(isNull(), nonNull(), requireNonNull())<br>
  Objects.isNull(Object obj)는 매개값이 null일 경우 true를 리턴한다. nonNull()는 반대이다. requireNonNull()는 세 가지로 오버로딩 되어 있다.
  - requireNonNull(T obj)
    - not null -> obj 리턴
    - null ->NullPointerException
  - requireNonNull(T obj, String message)
    - not null -> obj 리턴
    - null -> NullPointerException(message)
  - requireNonNull(T obj, Supplier<String>msgSupplier)
    - not null -> obj 리턴
    - null -> NullPointerException(msgSupplier.get())
- 객체 문자 정보(toString())
  - toString(Object o)  //(리턴타입 String)
    - not null -> o.toString()
    - null -> "null"
  - toString(Object o, String nullDefault)  //리턴타입(String)
    - not null -> o.toString()
    - null -> nullDefault

> System 클래스

자바 프로그램은 운영체제상에서가 아니라 JVM 위에서 실행되기 때문에 운영체제의 모든 기능을자바 코드로 직접 접근하기란 어렵다. 하지만 java.lang 패키지에 속하는 Syetem 클래스를 이용하면 일부 기능을 이용할 수 있다. Sustem 클래스의 모든 필드와 메소드는 정적 필드와 정적 메소드로 구성되어 있다.
- 프로그램 종료(exit())<br>
  강제적으로 JVM을 종료시킬 때 호출한다. exit()메소드는 int 매개값을 지정하도록 되어 있는데, 이것을 종료 상태값 이라고 한다. 일반적으로 정상 종료일 경우 0, 비정상 종료일 경우 이외의 값을 준다. *ex) System.exit(0);*<br>
  만약 특정 값이 입력되었을 경우에만 종료하고 싶다면 자바의 보안 관리자를 직접 설정해서 종료 상태값을 확인하면 된다. exit()메소드가 실행되면 보안 관리자의 checkExit()메소드가 자동 호출되는데, 이 메소드에서 종료 상태값을 조사해서 특정 값이 입력되지 않으면 SecurityException을 발생시켜 System.exit()를 호출한 곳에서 예외 처리를 할수 있도록 해준다. checkExit()가 정상적으로 실행되면 JVM은 종료된다.
  ```java
  System.setSecurityManager(new SecurityManager() {
      @Override
      public void chechExit(int status) {
          if (status != 5) {
              //5가 입력되지 않으면 예외를 발생시킨다.
              throw new SecurityException();
          }
      }
  });

  //예외 처리
  try {
      System.exit(i);
  } catch(SecurityException e) {}
  ```
- 쓰레기 수집기 실행(gc())<br>
  쓰레기 수집기 실행코드 System.gc();를 해도, 직접 코드로 실행 시킬 수는 없다. JVM에게 가능한 빨리 실행해달라고 요청할 뿐이다.
- 현재 시각 읽기(currentTimeMillis(), nanoTime())<br>
  두 메소드는 컴퓨터의 시계로부터 현재 시간을 읽어서 각각 밀리세컨드(1/1000초) 단위와 나노세컨드(1/1000000000초) 단위의 long값을 리턴한다.
  ```java
  long time = System.currentTimeMillis();
  long time = System.nanoTime();
  ```
  프로그램 시작시 시각을 읽고, 끝날 때 시각을 읽어서 차이를 구하면 프로그램 실행 소요 시간을 구할 수 있다.
- 시스템 프로퍼티 읽기(getProperty())<br>
  - 시스템 프로퍼티는 JVM이 시작할 때 자동 설정되는 시스템의 속성값을 말한다. 예를 들어 운영체제의 종류 및 자바 프로그램을실행시킨 사용자 아이디, 버전 파일 경로 구분자 등이다. 시스템 프로퍼티는 키(key)와 값(value)으로 구성되어 있다.
    - (key)  java.version (자바의 버전) : (value)  1.8.0_20
    - java.home (사용하는 JRE의 파일 경로) : <jdk 설치경로>\jre
    - os.name (Operating system name) : Windowd 7
    - file.separator (File separator("/" on UNIX)) : \
    - user.name (사용자의 이름) : 사용자계정
    - user.home (사용자의 홈 디렉토리) : C:\Users\사용자계정
    - user.dir (사용자가 현재 작업중인 디렉토리 경로) : 다양<br>
    ```java
    String value = System.getProperty(String key);
    ```
  - System.getProperties() 메소드는 모든 (키,값) 쌍을 저장하고 있는 Properties 객체를 리턴한다. 이 객체의 keySet() 메소드를 호출하면 키만으로 구성된 Set 객체를 얻을 수 있다. getProperty 메소드와 함께 활용하면 키와 값을 모두 출력할 수 있다.
- 환경 변수 읽기(getenv())
  - 대부분의 운영체제는 실행되는 프로그램들에게 유용한 정보를 제공할 목저긍로 환경 변수(Environment Variable)를 제공한다. 환경 변수는 프로그램상의 변수가 아니라, 운영체제에서 이름과 값으로 관리되는 문자열의 정보다. 환경 변수는 운영체제가 설치될 때 기본적인 내용이 설정되고, 사룔자가 직접 설정하거나 응용 프로그램이 설치될 때 자동적으로 추가 설정되기도 한다. 환경 변수 설정법은 운영체제마다 조금씩 다르다. 
  - 자바 프로그램에서는 환경 변수의 값이 필요할 경우 System.getenv() 메소드를 사용한다. 매개값으로 환경 변수 이름을 주면 값을 리턴한다.
    ```java
    String value = System.getenv (String name);
    //ex)
    String javaHome = System.getenv("JAVA_HOME");
    ```

> Class 클래스

자바는 클래스와 인터페이스의 메타 데이터(클래스의 이름, 생성자 정보, 필드 정보, 메소드 정보)를 java.lang 패키지에 소속된 Class 클래스로 관리한다.
- Class 객체 얻기(getClass(), forName())
  - Class 는 생성자를 감추고 있기 때문에 new 연산자로 객체를 만들 수 없다.
  - 프로그램에서 Class객체를 얻기 위해서는 Object 클래스가 가지고 있는 getClass() 메소드를 이용하면 된다.<br>
  *ex) Class clazz = obj.getClass();*<br>
  getClass() 메소드는 해당 클래스로 객체를 생성했을 때만 사용할 수 있다.
  - 정적 메소드인 forName()는 클래스 전체 이름(패키지 포함)을 매개값으로 받고 Class 객체를 리턴한다. 매개값으로 주어진 클래스를 찾지 못하면 ClassNotFoundException 예외를 발샐시키기 때문에 예외 처리가 필요하다.
- 리플렉션(getDeclaredConstructors(), getDeclaredFields(), getDeclaredMethods())
  Class 객체를 이용하면 클래스의 생성자, 필드, 메소드 정보를 알 수 있다. 이것을 리플렉션(Reflection)이라고 한다.
  ```java
  Constructor[] constructors = clazz.getDeclaredConstructors();
  Field[] fields = clazz.getDeclaredFields();
  Method[] methods = clazz.getDeclaredMethods();
  ```
  Constructor, Field, Method 클래스는 모두 java.lang.reflect 패키지에 소속되어 있고, 위의 세 메소드는 각각의 배열을 리턴한다. 단, getDeclaredField()와 getDeclaredMethod()는 클래스에 선언된 멤버만 가져오고 상속된 멤버는 가져오지 않는다. 만약 상속된 멤버도 얻고 싶다면 getFields(), getMethods()를 이용해야 한다. 단, 이 메소드는 public 멤버만 가져온다.
- 동적 객체 생성(newInstance())
  - Class 객체를 이용하면 new 연산자를 사용하지 않아도 동적으로 객체를 생성할 수 있는데, 코드 작성 시가 아닌 런타임 시에 클래스 이름이 결정되는 경우 매우 유용하다.
    ```java
    try {
        /*Class.forName()메소드로 Class 객체를 얻은 다음 newInstance()
        메소드를 호출하면 Object 타입의 객체를 얻을 수 있다.*/
        Class clazz = Class.forName("런타임 시 결정되는 클래스 이름");
        Object obj = clazz.newInstance();
    } catch (ClassNotFoundException e) {
    } catch (InstantiationException e) {
        //해당 클래스가 추상클래스이거나 인터페이스일 경우 발생
    } catch (IllegalAccessException e) {
        //클래스나 생성자가 접근 제한자로 인해 접근할 수 없을 경우 발생
    }
    ```
  - newInstance()메소드는 기본 생성자를 호출해서 객체를 생성한다. 매개 변수가 있는 생성자를 호출하려면 리플렉션으로 Constructor 객체를 얻어 newInstance() 메소드를 호출하면 된다. newInstance() 메소드의 리턴 타입은 Object 이므로 이것을 원래 클래스 타입으로 변환해야만 메소드를 사용할 수 있다. 하지만 원래 클래스 타입을 모른다. 이 땐, 인터페이스에 사용하고자 하는 메소드를 선언하고, 구현 클래스를 만든 뒤 newInstance()시 인터페이스 타입으로 캐스팅해서 인터페이스로 메소드를 사용하면 된다.

>String 클래스

- String 생성자<br>
  - 자바의 문자열은 java.lang 패키지의 String 클래스의 인스턴스로 관리된다. 문자열 리터럴은 String 객체로 자동 생성되지만, String 클래스의 다양한 생성자를 이용해서 직접 String 객체를 생성할 수도 있다. 파일의 내용을 읽거나, 네트워크를 통해 받은 데이터는 보통 byte[] 배열이므로 이것을 문자열로 변환하기 위해 사용되는 생성자들이 많다.
    ```java
    //배열 전체를 String 객체로 생성
    String str = new String(byte[] bytes);
    //지정한 문자셋으로 디코딩
    String str = new String(byte[] bytes, String charsetName);

    //배열의 offset 인덱스 위치부터 length만큼 String 객체로 생성
    String str = new String(byte[] bytes, int offset, int length);
    //지정한 문자셋으로 디코딩
    String str = new Stirng(byte[] bytes, int offsetm int length, 
    String charsetName);
    ```
  - 키보드로부터 읽은 바이트 배열을 문자열로 변환하는 경우, System.in.read()메소드는 키보드에서 입력한 내용을 매개값으로 주어진 바이트 배열에 저장하고 읽은 바이트 수를 리턴한다. 예를 들어 Hello 를 입력 후 엔터 키를 눌렀다면 Hello + 캐리지리턴(\r) + 라인피드(\n)의 코드값이 바이트 배열에 저장되고, 총 7개의 바이트를 읽기 때문에 7을 리턴한다.
- String 메소드
  - 리턴타입 | 메소드명(매개변수) | 설명
  - char  charAt(int index) : 특정 위치의 문자 리턴
  - boolean  equals(Object anObject) : 두 문자열을 비교
  - byte[]  getBytes() : byte[]로 리턴(시스템의 기본 문자셋으로 인코딩된 바이트 배열)
  - byte[]  getBytes(Charset charset) : 주어진 문자셋으로 인코딩한 byte[]로 리턴, 잘못된 문자셋을 매개값으로 줄 경우, java.io.UnsupportedEncodingException 발생
  - int  indexOf(String str) : 문자열 내에서 주어진 문자열의 위치를 리턴, 만약 주어진 문자열이 포함되어 있지 않으면 -1을 리턴
  - int  length() : 총 문자의 수를 리턴
  - String  replace(CharSequence target, CharSequence replacament) : target 부분을 replacement로 대치한 새로운 문자열을 리턴
  - String  substring(int beginIndex) : beginIndex 위치에서 끝까지의 문자열을 새로운 문자열로 리턴
  - String  substring(int beginIndex, int endIndex) : beginIndex 위치에서 endIndex 전까지의 문자열을 새로운 문자열로 리턴
  - String  toLowerCase() : 알파벳 소문자로 변환한 새로운 문자열을 리턴
  - String  toUpperCase() : 알파벳 대문자로 변환한 새로운 문자열을 리턴
  - String  trim() : 앞뒤 공백을 제거한 새로운 문자열을 리턴
  - String  valueOf(int i), valueOf(double d) : 기본 타입값을 문자열로 리턴

> StringTokenizer 클래스

문자열이 특정 구분자(delimiter)로 연결되어 있을 경우, 구분자를 기준으로 부분 문자열을 분리하기 위해서는 String의 split()메소드를 이용하거나, java.util 패키지의 StringTokenizer 클래스를 이용하면 된다.
- split() 메소드
  ```java
  String[] result = "문자열".split("정규표현식");
  //정규 표현식을 구분자로 해서 문자열을 분리한 후, 배열에 저장하고 리턴한다.
  //ex)
  String text = "홍길동&이수홍,박연수,김자바-최명호"
  String[] result = text.split("&|,|-");//여러개면 |로 구별한다.
  ```
- StringTokenizer 클래스
  ```java
  //문자열이 한 종류의 구분자로 연결되어 있을 경우!
  StringTokenizer st = new StringTokenizer("문자열", "구분자");
  //구분자 생략 시 공백이 기분 구분자가 된다.

  //ex)
  String text = "홍길동/이수홍/박연수";
  //StringTokenizer 객체 생성
  StringTokenizer st = new StringTokenizer(rext, "/");
  ```
  - StringTokenizer 클래스는 다음의 메소드를 가지고 있다.
    - int  countTokens() : 꺼내지 않고 남아 있는 토큰의 수
    - boolean  hasMoreTokens() : 남아 있는 토큰이 있는지 여부
    - String  nextToken() : 토큰을 하나씩 꺼내옴
    - nextToken() 메소드로 토큰을 하나 꺼내오면 해당 객체에는 해당 토큰이 없어진다. 만약 더 이상 가져올 토큰이 없다면 java.util.NoSuchElementException 예외가 발생한다.
    - hasMoreTokens()로 꺼내올 토큰이 있는지 조사한 후 nextToken()메소드를 호출하는 것이 좋다.

> StringBuffer, StringBuilder 클래스

문자열을 저장하는 String은 내부의 문자열을 수정할 수 없다. +연산에서도 기존 문자열에 더하는 문자열이 추가된 새로운 String 객체가 생성된다. 이런 연산을 많이 하면 그만큼 String 객체가 늘어나기 때문에, 프로그램이 느려지는 요인이 된다. 따라서 문자열 변경 작업이 많을 경우에는 String 클래스보다는 java.lang 패키지의 StringBuffer, StringBuilder 클래스를 사용하는 것이 좋다. 이 두 클래스는 내부 버퍼(데이터를 임시로 저장하는 메모리)에 문자열을 저장해 두고, 그 안에서 추가/수정/삭제 작업을 할 수 있게 설계되어 있다.
- 두 클래스의 사용 방법은 동일하지만, StringBuffer는 멀티 스레드 환경에서 사용할 수 있도록 동기화가 적용되어 있어 스레드에 안전한 반면 StringBuilder는 단일 스레드 환경에서만 사용 가능하다.
- StringBuilder의 기본 생성자는 16개의 문자들을 저장할 수 있는 초기 버퍼를 만들고, StringBuilder(int capacity) 생성자는 매개값 만큼의 문자들을 저장할 수 있는 초기 버퍼를 만든다. (버퍼가 부족할 경우 자동으로 버퍼 크기를 늘리기 때문에 초기 버퍼의 크기는 그다지 중요하지 않다.) StringBuilder(String str) 생성자는 str로 주어진 매개값을 버퍼의 초기값으로 저장한다.
- StringBuilder 클래스의 메소드
  - append(...) : 문자열 끝에 주어진 매개값을 추가
  - Insert(int offset,...) : 문자열 중간에 주어진 매개값을 추가
  - delete(int start, int end) : 문자열의 일부분을 삭제
  - deleteCharAt(int index) : 문자열에서 주어진 index의 문자를 삭제
  - replace(int start, int end, String str) : 문자열의 일부분을 다른 문자열로 대치
  - reverse() : 문자열의 순서를 바꿈
  - setCharAt(int index, char ch) : 문자열에서 주어진 index의 문자를 다른 문자로 대치

> 정규 표현식과 Patter 클래스

문자열이 정해져 있는 형식(정규 표현식: Regular Expression)으로 구성되어 있는지 검증해야 하는 경우가 있다. (이메일, 전화번호를 사용자가 제대로 입력했는지 검증해야 하는 경우 등)
- 정규 표현식 작성 방법
  - API 도큐먼트에서 java.util.regex.Patter 클래스를 찾아 summary of regular-expression constructs를 참조하면 된다.
  - 정규표현식은 문자 또는 숫자 기호와 반복 기호가 결함된 문자열이다.
    - [] : 한개의 문자
      - [abc] : abc중 하나의 문자
      - [^abc] : abc 이외의 하나의 문자
      - [a-zA-Z] : a~z,A~Z 중 하나의 문자
    - \d : 한개의 숫자, [0-9]와 동일
    - \s : 공백
    - \w : 한 개의 알파벳 또는 한 개의 숫자, [a-zA-Z_0-9]와 동일
    - ? : 없음 또는 한 개
    - * : 없음 또는 한 개 이상
    - + : 한 개 이상
    - {n} : 정확히 n개
    - {n,} : 최소한 n개
    - {n, m} : n개부터 m개까지
    - () : 그룹핑
    ```java
    ex)
    (02|010)-\d{3,4}-\d{4}  //전화번호를 위한 정규표현식
    //02또는010, -포함, 3~4자리 숫자, -포함, 4자리 숫자

    \w+@\w+\.\w+(\.\w+)?  //이메일을 위한 정규표현식
    /*한개이상의 알파벳 또는 숫자, @, 한개이상의 알파벳 또는 숫자, .,
    한개이상의 알파벳 또는 숫자, \.\w+이 없거나 한 번 더 올 수 있음*/
    //\. : 문자로서의 .
    //. : 모든 문자 중 한 개의 문자
    ```
- Pattern 클래스
  - 문자열을 정규 표현식으로 검증하는 기능은 java.util.regex.Pattern 클래스의 정적 메소드인 matches() 메소드가 제공한다.
    ```java
    boolean result = Pattern.matches("정규식", "검증할 문자열");
    //일치할 경우 true를 리턴
    ```

> Arrays 클래스

단순 배열 복사는 System.arraycopy메소드를 사용할 수 있으나, Arrays 클래스는 배열 조작 기능(배열의 복사, 항목 정렬, 항목 검색 등)을 가지고 있다. Arrays 클래스의 모든 메소드는 정적 메소드이다.
- 배열 복사
  - 타겟배열  copyOf(원본배열, 복사할 길이) : 원본 배열의 0번 인덱스에서 복사할 길이만큼 복사한 배열 리턴, 복사할 길이는 원본 배열의 길이보다 커도 되며, 타겟배열의 길이가 된다.
  - 타겟배열  copyOfRange(원본배열, 시작인덱스, 끝인덱스) : 원본 배열의 시작 인덱스에서 끝 인덱스(불포함)까지 복사한 배열 리턴
    ```java
    //단순 배열 복사는 System.arraycopy() 메소드 사용 가능
    System.arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
    //원본배열, 원본시작인덱스, 타겟배열, 타겟배열 복사당할 시작인덱스, 복사개수
    ```
- 배열 항목 비교
  - boolean  equals(배열, 배열) : 두 배열의 얕은 비교(중첩 배열의 항목은 비교하지 않음)
  - equals()는 1차 항목만 비교한다.
  - boolean  deepEquals(배열, 배열) : 두 배열의 깊은 비교(중첩 배열의 항목까지 비교)
  - deepEquals()는 1차 항목이 서로 다른 배열을 참조할 경우 중첩된 배열의 항목까지 비교한다.
- 배열 항목 정렬
  - void  sort(배열) : 배열의 전체 항목을 오름차순으로 정렬
  - 기본 타입 또는 String 배열은 Arrays.sort()메소드의 매개값으로 넣어주면 자동으로 오름차순 정렬이 된다. 사용자 정의 클래스 타입일 경우에는 클래스가 Comparable 인터페이스를 구현하고 있어야 정렬이 된다.
- 배열 항목 검색
  - 배열 항목을 검색하려면 먼저 Arrays.sort()메소드로 항목들을 오름차순을 정렬 후, Arrays.binarySearch() 메소드로 항목을 찾아야 한다.
  - int  binarySearch(배열, 찾는 값) : 전체 배열 항목에서 찾는 값이 있는 인덱스 리턴
- 기타
  - void  fill(배열, 값) : 전체 배열 항목에 동일한 값을 저장
  - void  fill(배열, 시작인덱스, 끝인덱스, 값) : 시작 인덱스부터 끝 인덱스까지의 항목에만 동일한 값을 저장

> Wrapper(포장) 클래스

- 자바는 기본 타입의 값을 갖는 객체를 생성할 수 있다. 이런 객체를 포장 객체라고 하는데, 기본 타입의 값을 내부에 두고 포장하기 때문이다. 포장하고 있는 기본 타입 값은 외부에서 변경할 수 없고, 변경하고 싶다면 새로운 포장 객체를 만들어야 한다.
- 포장 클래스는 java.lang 패키지에 포함되어 있는데, 기본 타입에 대응되는 클래스들이 있다.
  - byte - Byte
  - char - Character
  - short - Short
  - int - Integer
  - long - Long
  - float - Float
  - double - Double
  - boolean - Boolean
- 박싱(Boxing)과 언박싱(Unboxing)
  - 기본 타입의 값을 포장 객체로 만드는 과정을 박싱이라 하고, 반대로 포장 객체에서 기본 타입의 값을 얻어내는 과정을 언박싱이라고 한다. 박싱은 간단하게 포장 클래스의 생성자 매개값으로 기본 타입의 값 또는 문자열을 넘겨주면 된다.<br>
  *ex) Byte obj = new Byte(10); , Integer obj = new Integer("100"); , Character obj = new Character('가');*
  - 생성자를 이용하지 않아도 포장 클래스마다 가지고 있는 정적 valueOf()메소드를 사용할 수도 있다.<br>
  *ex) Integer obj = Integer.valueOf(1000); ,<br>
  Integer obj = Integer.valueOf("1000");*
  - 이렇게 박싱된 포장 객체에서 언박싱하기 위해서는 각 포장 클래스마다 가지고 있는 "기본타입명 + Value()"메소드를 호출하면 된다.<br>
  *ex) num = obj.byteValue(); , ch = obj.charValue(); ,<br>
  bool = obj.booleanValue();*
- 자동 박싱과 언박싱
  - 자동 박싱은 포장 클래스 타입에 기본값이 대입될 경우 발생한다.
    ```java
    Integer obj = 100;
    /*int타입 값을 해당 포장클래스타입 변수에 대입하면
    자동박싱이 일어나 힙 영역에 Integer 객체가 생성된다.*/
    ```
  - 자동 언박싱은 기본 타입에 포장 객체가 대입될 경우에 발생한다.
    ```java
    Integer obj = new Integer(200);
    int value1 = obj; //포장 객체가 기본 타입에 대입 시 자동언박싱
    int value2 = obj + 100;
    //포장클래스 객체와 해당 타입값 연산 시 자동 언박싱되어 연산
    ```
- 문자열을 기본 타입 값으로 변환
  - 포장 클래스는 문자열을 기본 타입 값으로 변환할 때에도 많이 사용된다. 대부분의 포장 클래스에는 "parse + 기본타입"명으로 되어 있는 정적 메소드가 있다. 이 메소드는 문자열을 매개값으로 받아 기본 타입 값으로 변환한다.<br>
  *ex) num = Byte.parseByte("10");*
- 포장 값 비교
  - 포장 객체는 내부의 값을 비교하기 위해 ==,!= 연산자를 사용할 수 없다. 이 연산자는 내부의 값이 아니라 포장 객체의 참조를 비교하기 때문이다. 단, 박싱된 값이 boolean(true,false), char(\u0000 ~ \u007f), byte,short,int(-128 ~ 127) 사이의 값이라면 ==,!= 연산자로 내부의 값을 바로 비교할 수 있다.
  - 그 이외의 경우에는 내부의 값만 비교하려면 언박싱한 값을 얻어 비교해야 한다.
  - 아니면 equals() 메소드로 내부 값을 비교해야 한다. 포장 클래스의 equals() 메소드는 내부의 값을 비교하도록 오버라이딩 되어 있다.

> Math, Random 클래스

- Math 클래스<br>
  java.lang.Math 클래스는 수학 계산에 사용할 수 있는 메소드를 제공한다. Math 클래스가 제공하는 메소드는 모두 정적 메소드이다.
  - int abs(int a), double abs(double a) : 절대값 리턴
  - double celi(double a) : 올림값 리턴
  - douvle floor(double a) : 버림값 리턴
  - int max(int a, int b), double max(double a, double b) : 최대값 리턴
  - int min(int a, int b), double min(double a, double b) : 최소값 리턴
  - double random() : 0.0 이상 1.0 미만의 랜덤값 리턴(범위 지정은 리턴값에 n을 곱한 후 int로 캐스팅 한 뒤 n2를 더해주면 n2이상 n+n2미만의 정수 랜덤값이 나온다.)
  - double rint(double a) : 가까운 정수의 실수값 리턴
  - long round(double a) : 소수점 첫째 자리에서 반올림값 리턴(원하는 자리가 있을 경우 10의 n제곱을 곱한 후 리턴값을 얻어서 다시 나눠주면 된다.)
- Random 클래스<br>
  java.util.Random 클래스는 난수를 얻어내기 위해 다양한 메소드를 제공한다. Math.random()메소느는 0.0이상 1.0미만의 double 난수를 얻는데만 사용한다면, Random 클래스는 boolean, int, long, float, double 난수를 얻을 수 있다. 또한 종자값(seed)를 설정할 수 있다. 종자값이 같으면 같은 난수를 얻는다.
  - Random 클래스로부터 Random 객체를 생성하는 방법
    - 생성자 Random() : 호출 시마다 다른 종자값(현재 시간 이용)이 자동 설정된다.
    - 생성자 Random(long seed) : 매개값으로 주어진 종자값이 설정된다.
  - Random 클래스가 제공하는 메소드
    - boolean  nextBoolean() : boolean 타입의 난수를 리턴
    - double  nextDouble() : double 타입의 난수를 리턴(0.0이상 1.0미만)
    - int  nextInt() : int 타입의 난수를 리턴(-2<sup>31</sup>이상 2<sup>31</sup>-1 이하)
    - int  nextInt(int n) : int 타입의 난수를 리턴(0 이상 n 미만)
  
> Date, Calendar 클래스

자바는 java.util패키지에 시스템의 날짜 및 시각을 읽을 수 있도록 Date와 Calendar 클래스를 제공한다.
- Date 클래스<br>
  - Date는 날짜를 표현하는 클래스이다. 주로 객체간에 날짜 정보를 주고 받을 때 사용된다. Date() 생성자만 주로 사용한다.
  - toString() 메소드는 현재 날짜를 영문의 문자열로 리턴한다.
  - 특정 문자열 포맷으로 얻고 싶다면 java.text.SimpleDateFormat 클래스를 이용하면 된다.
    ```java
    SimpleDateFormat sdf = new SimpleFateFormat(
        "yyyy년 MM월 dd일 hh시 mm분 ss초");
    String strNow2 = sdf.format(now);
    System.out.println(strNow2);
    ```
- Calendar 클래스
  - Calendar 클래스는 달력을 표현한 클래스이다. 추상 클래스이므로 new 연산자를 사용해서 인스턴스를 생성할 수 없다. 날짜와 시간을 계산하는 방법이 지역과 문화 등에 따라 다르기 때문이다.
  - 그래서 꼭 필요한 메소드들만 선언되어 있고, 특정한 계산로직은 하위 클래스에서 구현하도록 되어 있다.
  - 특별한 경우가 아니라면 Calendar 클래스의 정적 메소드인 getInstance() 메소드를 이용하면 현재 운영체제에 설정되어 있는 시간대(TimeZone)를 기준으로 한 Calendar 하위 객체를 얻을 수 있다.
    ```java
    Calendar now = Calendar.getInstance();
    //객체를 얻었다면 get() 메소드를 이용해서 정보를 얻을 수 있다.
    int year = now.get(Calendar.YEAR);
    int month = now.get(Calendat.MONTH) + 1;
    int day = now.get(Calendar.DAY_OF_MONTH);
    int week = now.get(Calendar.DAY_OF_WEEK);
    int amPm = now.get(Calendar.AM_PM);
    int hour = now.get(Calendar.HOUR);
    int minute = now.get(Calendar.MINUTE);
    int second = now.get(Calendar.SECOND);
    //위에 사용된 매개값은 모두 Calendar 클래스에 선언되어 있는 상수들이다.
    ```
  - 다른 시간대, 예를 들어 미국/LA의 날짜와 시간을 출력하려면, Calendat 클래스의 오버로딩된 다른 getInstance() 메소드를 이용하면 간단하게 다른 시간대의 Calendar를 얻을 수 있다. 알고 싶은 시간대의 java.util.TimeZone 객체를 얻어, Calendat.getInstance() 메소드의 매개값으로 넘겨주면 된다.
    ```java
    TimeZone timeZone = TimeZone.getTimeZone("America/Los_Angeles");
    Calendar now = Calendar.getInstance(timeZone);
    ```
  TimeZone.getTimeZone() 메소드의 매개값은 TimeZone 클래스의 정적 메소드인 getAvailableIDs()를 호출하여 얻은 시간대 문자열 중 하나를 사용하면된다.

> Format 클래스

자바는 많은 수의 데이터의 복잡한 형식 변환과 계산을 쉽게 해결하기 위해 형식 클래스를 제공한다. 형식 클래스는 java.text 패키지에 포함되어 있다.
- **숫자 형식 클래스(DecimalFormat)**<br>
  DecimalFormat은 숫자 데이터를 원하는 형식으로 표현하기 위해서 패턴을 사용한다. 
- **날짜 형식 클래스(SimpleDateFormat)**<br>
  java.text.SimpleDateFormat 클래스는 Date 클래스의 toStrinf() 메소드와 달리 특정 문자열 포맷으로 날짜를 얻을 수 있다. SimpleDateFormat 클래스도 날짜를 원하는 형식으로 표현하기 위해서 패턴을 사용한다.
  - 패턴 작성에 사용되는 기호
    - y : 년, M : 월, d : 일, D : 월 구분이 없는 일(1~365)
    - E : 요일, a : 오전/오후, w : 년의 몇 번째 주, W : 월의 몇 번째 주
    - H : 시(0~23), h : 시(1~12), K : 시(0~11), k : 시(1~24)
    - m : 분, s : 초, S : 밀리세컨드(1/1000초)
  - 패턴에는 자릿수에 맞게 기호를 반복해서 작성할 수 있다. 적용할 패턴을 작성하면 이 패턴을 SimpleDateFormat의 생성자 매개값으로 지정해서 객체를 생성하면 된다. 그 후 format() 메소드를 호출해서 패턴이 적용된 문자열을 얻는다.
    ```java
    SimpleDateFormat sdf = new SimpleDateFormat("yyyy년 MM월 dd일");
    String strDate = sdf.format(new Date());
    ```
- **문자열 형식 클래스(MessageFormat)**<br>
  데이터를 파일에 저장하거나, 네트워크에 전송할 때, 데이터베이스 SQL문을 작성할 때 등 많은 부분에서 일정한 형식의 문자열을 사용한다. MessageFormat 클래스를 사용하면 문자열에 데이터가 들어갈 자리를 표시해 두고, 프로그램이 실행하면서 동적으로 데이터를 삽입해 문자열을 완성시킬 수 있다.
  ```java
  //ex
  String id = "blue";
  String name = "함형규";
  String tel = "010-123-1234";
  String result = "회원ID: " + id + "\n회원이름: " 
                  + name + "\n회원전화: " + tel;
  //MessageFormat클래스 사용 시
  String message = "회원ID: {0} \n회원이름: {1} \n회원전화: {2}";
  String result = MessageFormat.format(message, id, name, tel);
  //MessageFormat은 정적 format() 메소드를 호출해서 완성된 문자열을 리턴한다.
  Object[] arguments = {id, name, tel};
  String result = MessageFormat.format(message, arguments);
  //값 나열 대신 배열을 대입해도 된다.

> java.time 패키지

- 자바8부터는 날짜와 시간을 조작하거나 비교하는 기능을 위해 날짜와 시간을 나타내는 여러 API가 새롭게 추기되었다. 이 API는 java.util패키지가 아닌 별도의 java.time 패키지와 하위 패키지로 제공된다.
  - java.time : LocalDate, LocalTime, LocalDateTime, ZonedDateTime을 포함한다. 이 클래스들은 ISO-8601에 정의된 달력 시스템에 기초한다.
  - java.time.chrono : ISO-8601에 정의된 달력 시스템 이외에 다른 달력 시스템이 필요할 때 사용할 수 있는 API들이 포함되어 있다.
  - java.time.format : 날짜와 시간을 파싱하고 포맷팅하는 API들이 포함되어 있다.
  - java.time.temporal : 날짜와 시간을 연산하기 위한 보조 API들이 포함되어 있다.
  - java.time.zone : 타임존을 지원하는 API들이 포함되어 있다.
- 날짜와 시간 객체 생성<br>
  java.time 패키지에는 날짜와 시간을 표현하는 5개의 클래스가 있다.
  - LocalDate는 로컬 날짜 클래스로 날짜 정보만을 저장한다.
    - now() 정적 메소드는 컴퓨터의 현재 날짜 정보를 저장한 LocalDate 객체를 리턴한다.
    - of() 정적 메소드는 매개값으로 주어진 날짜 정보를 저장한 LocalDate 객체를 리턴한다.
      ```java
      LocalDate currDate = LocatDate.now();
      LocalDate targetDate = LocalDate.of(int yearm int month,
                                           int dauOfMonth);
      ```
  - LocalTime은 로컬 시간 클래스로 시간정보만을 저장한다. 마찬가지로 now()와 of() 정적 메소드를 가진다.
    ```java
    LocalTime currTime = LocalTime.now();
    LocalTime targetTime = LocalTime.of(int hour, int minute,
                                   int second, int nanoOfSecond);
    ```
  - LocalDateTime은 날짜와 시간 정보를 모두 저장할 수 있다. 마찬가지로 now()와 of() 정적 메소드를 가진다.
    ```java
    LocalDateTime currDateTime = LocalDateTime.now();
    LocalDateTime targetDateTime = LocalDateTime.of(
      int year, int month, int datOfMonth, int hour, int minute,
       int second, int nanoOfSecond);
    ```
  - ZoneDateTime은 ISO-8601 달력 시스템에서 정의하는 타임존의 날짜와 시간을 저장하는 클래스이다. 저장 형태는 *2014-04-21T07:50:24.017+09:00[Asia/Seoul]*와 같이 맨 뒤에 타임존에 대한 정보(+-존오프셋[존아이디]가 추가적으로 붙는다. 존오프셋은 협정세계시(UTC)와 차이나는 시차를 말한다. ZonedDateTime은 now() 정적 메소드에 ZoneId를 매개값으로 주고 얻을 수 있다. ZoneId는 of()메소드로 얻을 수 있는데, 매개값은 java.util.TimeZone의 getAvailableIDs()메소드가 리턴하는 유효한 값 중 하나이다.
    ```java
    ZonedDateTime utcDateTime = ZonedDateTime.now(ZoneId.of("UTC"));
    ZonedDateTime londonDateTime = ZonedDateTime.now(ZoneId.of(
                                              "Eutope/London"));
    ZonedDateTime seoulDateTime = ZonedDateTime.now(ZoneId.of(
                                              "Asia/Seoul"))
    ```
  - Instant 클래스는 특정시점의 타임 스탬프로 사용된다. 주로 특정한 두 시점간의 시간적 우선순위를 따질 때 사용된다. java.util.Date와 가장 유사하지만, Date는 로컬 컴퓨터의 현재날짜 및 시간정보를 기준으로 하지만 Instant는 협정세계시(UTC)를 기준으로 한다.
    ```java
    Instant instant1 = Instant.now();
    Instant instant2 = Instant.now();
    //isBefore(), isAfter()는 시간의 앞뒤 여부를 확인하는 메소드이다.
    if(instant1.isBefore(instant2)) {
      System.out.println("instant1이 빠름");
    } else if(instant1.isAfter(instant2)) {
      System.out.println("instant1이 늦음");
    } else {
      System.out.println("동일");
    }
    //until() 메소드는 두 시점간의 차이를 리턴한다.
    System.out.println("차이(nanos): "
             + instant1.until(instant2, ChromoUnit.NANOS));
    ```
- 날짜와 시간에 대한 정보 얻기<br>
  - LocalDate 클래스의 메소드
    - int getYear()
    - Month getMonth()
    - int getMonthValue()
    - int getDatOfYear()
    - int getDayOfMonth()
    - DayOfWeek getDayOfWeek()
    - boolean isLeapYear() //윤년여부
  - LocalTime 클래스의 메소드
    - int getHour()
    - int getMinute()
    - int getSecond()
    - int getNano()
  - LocalDateTime과 ZonedDateTime은 날짜와 시간 정보를 모두 갖고 있기 때문에 위의 메소드의 대부분을 가진다. 단, isLeapYear()는 LocatDate에만 있기 때문에 *toLocalDate()*메소드로 타입 변환 후에 사용할 수 있다.
  - ZonedDateTime 클래스가 추가적으로 제공하는 메소드
    - ZoneId getZone() //존아이디를 리턴(Asia/Seuoyl)
    - ZoneOffset getOffset() //존오프셋(시차)를 리턴
- 날짜와 시간을 조작하기<br>
  날짜와 시간 클래스들은 날짜와 시간을 조작하는 메소드와 상대 날짜를 리턴하는 메소드들을 가지고 있다.
  - 날짜와 시간을 대상으로 빼기와 더하기를 하는 메소드
    - LocalDate, LocalDateTime, ZonedDateTime 클래스
      - (리턴 타입은 해당 클래스 타입)
      - minusYears(long) : 년 빼기
      - minusMonths(long) : 달 빼기
      - minusWeeks(long) : 주 빼기
      - minusDays(long) : 일 빼기
      - plusYears(long) : 년 더하기
      - plusMonths(long) : 월 더하기
      - plusWeeks(long) : 주 더하기
      - plusDays(long) : 일 더하기
    - LocalTime, LocalDateTime, ZonedDateTime 클래스
      - (리턴 타입은 해당 클래스 타입)
      - minusHours(long) : 시간 빼기
      - minusMinutes(long) : 분 빼기
      - minusSeconds(long) : 초 빼기
      - minusNanos(long) : 나노초 빼기
      - plusHours(long) : 시간 더하기
      - plusMinutes(long) : 분 더하기
      - plusSeconds(long) : 초 더하기
      - plusNanos(long) : 나노초 더하기
    - 위 각각의 메소드들은 해당 클래스 타입을 리턴하기 때문에 도트 연산자로 순차적으로 계속 호출할 수 있다.
  - 날짜와 시간을 변경하는 메소드
    - LocalDate, LocalDateTime, ZonedDateTime 클래스
      - (리턴 타입은 해당 클래스 타입)
      - withYear(int) : 년 변경
      - withMonth(int) : 월 변경
      - withDayOfMonth(int) : 월의 일 변경
      - withDayOfYear(int) : 년의 일 변경
      - with(TemporalAdjuster adjuster) : 상대 변경<br>
        현재 날짜를 기준으로 해(달)의 첫 번째 일 또는 마지막 일, 달의 첫 번째 요일, 지난 요일 및 돌아오는 요일 등 상대적인 날짜를 리턴한다. 매개값은 TemporalAdjuster의 정적 메소드를 호출하면 얻을 수 있다.(p.558)
    - LocalTime, LocalDateTime, ZonedDateTime 클래스
      - (리턴 타입은 해당 클래스 타입)
      - withHour(int) : 시간 변경
      - withMinute(int) : 분 변경
      - withSecond(int) : 초 변경
      - withNano(int) : 나노초 변경
- 날짜와 시간을 비교하기<br>
  - 날짜와 시간 클래스들은 비교하거나 차이를 구하는 메소드들을 가진다. (p.560)
  - Period와 Duration은 각각 날짜(년, 달, 일)와 시간(시, 분, 초, 나노초)의 양을 나타내는 클래스이다.
    - Period 클래스의 메소드
      - int getYears(), (Months,Days) -> 년,달,일의 차이
    - Duration 클래스의 메소드
      - int getSeconds(), getNano() -> 초, 나노초의 차이
  - between() 메소드는 Period와 Duration 클래스, 그리고 ChronoUnit 열거 타입에도 있다. Period와 Duration에서는 년, 달, 일, 초의 단순 차이를 리턴하고, ChronoUnit에서는 전체 시간을 기준으로 차이를 리턴한다.
- 파싱과 포맷팅<br>
  날짜와 시간 클래스는 문자열을 파싱(parsing) 해서 날짜와 시간을 생성하는 메소드와 이와 반대로 날짜와 시간을 포맷팅(Formatting)된 문자열로 변환하는 메소드를 제공한다.
  - 파싱(Parsing) 메소드
    - parse(CharSequence)
      - LocalDate 클래스에서의 이 메소드는 기본적으로 ISO_LOCAL_DATE 포맷터를 사용해서 문자열을 파싱한다. ISO_LOCAL_DATE는 DateTimeFormatter의 상수로 정의되어 있는 "2024-05-03" 형식의 포맷터이다. 다른 포맷터를 이용해서 문자열을 파싱하고 싶다면 아래의 메소드를 사용하면된다.
    - parse(CharSequence, DateTimeFormatter)
      - DateTimeFormatter는 ofPatter() 메소드로 정의할 수도 있다. (p.564)
      - DateTimeFormatter에는 표준화된 포맷터들이 상수로 미리 정의되어 있기 때문에 메소드를 사용하지 않고 바로 이용할 수 있다. (p.564)
      - 만약 포맷터의 형식과 다른 문자열을 파싱하게 되면 DateTimeParseException이 발생한다.
  - 포맷팅(Formatting) 메소드
    - format(DateTimeFormatter formatter) 메소드는 날짜와 시간을 포맷팅된 문자열로 변환시켜 String 타입으로 리턴한다.
    - format()의 매개값인 DateTimeFormatter는 해당 형식대로 문자열을 리턴한다.