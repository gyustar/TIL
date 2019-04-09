## 16. 스트림과 병렬 처리

> 스트림 소개

스트림은 자바8부터 추가된 컬렉션(배열 포함)의 저장 요소를 하나씩 참조해서 람다식으로 처리할 수 있도록 해주는 반복자이다.
- 반복자 스트림
  ```java
  //List<String> 컬렉션에서 요소를 순차적 처리하기 위해 Iterator 반복자 사용
  List<String> list = Arrys.asList("홍", "신", "김");
  Iterator<String> iterator = list.iterator();
  while(iterator.hasNext()) {
      String name = iterator.next();
      Systam.out.println(name);
  }

  //Stream 으로 변경
  List<String> list = Arrays.asList("홍", "신", "김");
  Stream<String> stream = list.stream();
  stream.forEach( name -> System.out.prnintln(name));
  ```
  컬렉션(java.util.Collection)의 stream() 메소드로 스트림 객체를 얻고 나서 forEach 메소드로 컬렉션의 요소를 하나씩 얻는다. forEach() 메소드는 Consumer 함수적 인터페이스 타입의 매개값을 가진다.
  ```java
  void forEach(Consumer<T> action)
  ```
- 스트림의 특징
  - 람다식으로 요소 처리 코드를 제공한다. Stream이 제공하는 대부분의 요소 처리 메소드는 함수적 인터페이스 매개 타입을 가지기 때문에, 람다식 또는 메소드 참조를 이용해서 요소 처리 내용을 매개값으로 전달할 수 있다.
  - 내부 반복자를 사용하므로 병렬 처리가 쉽다. 외부 반복자(external iterator)란 개발자가 코드로 직접 컬렉션의 요소를 반복해서 가져오는 코드 패턴을 말한다. 반면 내부 반복자는 컬렉션 내부에서 요소들을 반복시키고, 개발자는 요소당 처리해야 할 코드만 제공하는 코드 패턴이다. 내부 반복자는 요소들의 반복 순서를 변경하거나, 멀티 코어 CPU를 최대한 활용하기 위해 요소들을 분배시켜 병렬 작업을 할 수 있게 도와주기 때문에 효율적으로 요소를 반복시킬 수 있다.
  - 스트림은 컬렉션의 요소에 대해 중간 처리와 최종 처리를 할 수 있다. 중간 처리에서는 매핑, 필터링, 정렬을 수행하고 최종 처리에서는 반복, 카운팅, 평균, 총합 등의 집계 처리를 수행한다.

> 스트림의 종류

- java.util.stream 패키지에는 스트림 API들이 포진하고 있다. 패캐지 내용을 보면 BaseStream 인터페이스를 부모로 해서 자식 인터페이스들이 상속 관계를 이루고 있다. 이 중 Stream은 객체 요소를 처리하는 스티림이고, IntStream, LongStream, DoubleStream은 각각 해당 기본 타입 요소를 처리하는 스트림이다. 이 스트림 인터페이스의 구현 객체는 컬렉션과 배열 말고도 다양한 소스로부터 얻을 수 있다.
  - 컬렉션
    - Stream<T>  java.util.Collection.stream(), java.util.Collection.parallelStream()
  - 배열
    - Stream<T>  Arrays.stream(T[]), Stream.of(T[])
    - IntStream  Arrays.stream(int[]), IntStream.of(int[])
    - LongStream  Arrays.stream(long[]), LongStream.of(long[])
    - DoubleStream  Arrays.stream(double[]), DoubleStream.of(double[])
  - int 범위
    - IntStream  IntStream.range(int, int), IntStream.rangeClosed(int, int)
  - long 범위
    - LongStream  LongStream.range(long, long), LongStream.rangeClosed(long, long)
  - 디렉토리
    - Stream<Path>  Files.find(Path, int, BiPredicate, FileVisitOption), Files.list(Path)
  - 파일
    - Stream<String>  Files.lines(Path, Charset), BufferedReader.lines()
  - 램덤 수
    - DoubleStream  Random.doubles(..)
    - IntStream  Random.ints()
    - LingStream  Random.longs()
  
> 스트림 파이프라인

대량의 데이터를 가공해서 축소하는 것을 일반적으로 리덕션(Reduction)이라고 하는데, 데이터의 합계, 평균값, 카운팅, 최대값, 최소값 등이 대표적인 리덕션의 결과물이라고 볼 수 있다. 그러나 컬렉션의 요소를 리덕션의 결과물로 바로 집계할 수 없는 경우에는 집계하기 좋도록 필터링, 매핑, 정렬, 그룹핑 등의 중간 처리가 필요하다.

- 중간 처리와 최종 처리
  - 스트림은 데이터의 중간처리와 최종 처리를 파이프라인(pipelines)으로 해결한다. 파이프라인은 여러 개의 스트림이 연결되어 있는 구조를 말한다. 최종 처리를 제외하고는 모두 중간 처리 스트림이다.
  - 중간 스트림이 생성될 때 요소들은 지연(lazy)되다가, 최종 처리가 시작되면 하나씩 중간 스트림에서 처리되고 최종 처리까지 오게 된다.
  - Stream 인터페이스에는 필터링, 매핑, 정렬 등의 많은 중간 처리 메소드가 있는데, 이 메소드들은 중간 처리된 스트림을 리턴한다. 그리고 다시 중간 처리 메소드를 호출해서 파이프라인을 형성한다.
    ```java
    //회원 컬렉션에서 남자,나이 필터링을 하고 최종 남자 평균 나이를 집계하는 파이프라인
    Stream<Member> maleFemaleStream = list.stream();
    Stream<Member> maleStream = maleFemaleStream.filter(
        m -> m.getSec() == Member.MALE;
    );
    IntStream ageStream = maleStream.mapToInt(Member :: getAge);
    OptionalDouble optionalDouble = ageStream.average();
    double ageAvg = optionalDouble.getAsDouble();

    //위 코드를 로컬 변수를 생략하고 연결하면 파이프라인 코드만 남는다.
    double ageAvg = list.stream()  //오리지날 스트림
        .filter( m -> m.getSex() == Member.MALE ) //중간 처리 스트림
        .mapToInt(Member :: getAge)               //중간 처리 스트림
        .average() //최종 처리
        .getAsDouble();
    ```
- 중간 처리 메소드와 최종 처리 메소드
  - 스트림이 제공하는 중간 처리와 최종 처리를 하는 메소드 (p.798)
  - 리턴 타입이 스트림이라면 중간 처리 메소드, 기본 타입이거나 OptionalXXX라면 최종 처리 메소드이다.

> 필터링(distinct(), filter())

필터링은 중간 처리 기능으로, 요소를 걸러내는 역할을 한다. distinct()와 filter() 메소드는 모든 스트림이 가지는 공통 메소드이다.
- 리턴타입 : Stream/IntStream/LongStream/DoubleStream
- 메소드 : distinct(), filter(Predicate), filter(IntPredicate), filter(LongPredicate), filter(DoublePredicate)

- distinct() 메소드는 중복을 제거하는데, Stream의 경우 Object.equals(Object)가 true이면 동일한 객체로 판단하고 중복을 제거한다. IntStream, LongStream, DoubleStream은 동일값일 경우 중복을 제거한다. 
- filter() 메소드는 매개값으로 주어진 Predicate가 true를 리턴하는 요소만 필터링한다.(남긴다.)

> 매핑(flatMapXXX(), mapXXX(), asXXXStream(), boxed())

매핑(mapping)은 중간 처리 기능으로, 스트림의 요소를 다른 요소로 대체하는 작업이다.

- flatMapXXX() 메소드
  - 요소를 대체하는 복수 개의 요소들로 구성된 새로운 스트림을 리턴한다. A요소가 A1, A2 요소로 대체되고, B요소가 B1, B2 요소로 대체될 경우 A1,A2,B1,B2 요소를 가지는 새로운 스트림이 생성된다.
    - Stream<R>  flatMap(Function<T, Stream<R>>) : T -> Stream<R> 대체
    - DoubleStream  flatMap(DoubleFunction<DoubleSream>) : double -> DoubleStream 대체
    - IntStream  flatMap(IntFunction<IntSream>) : int -> IntStream 대체
    - LongStream  flatMap(LongFunction<LongSream>) : long -> LongStream 대체
    - DoubleStream  flatMapToDouble(Function<T, DoubleSream>) : T -> DoubleStream 대체
    - IntStream  flatMapToInt(Function<T, IntSream>) : T -> IntStream 대체
    - LongStream  flatMapToLong(Function<T, LongSream>) : T -> LongStream 대체
- mapXXX() 메소드
  - 요소를 대체하는 요소로 구성된 새로운 스트림을 리턴한다. A요소가 C요소로 대체되고, B요소가 D요소로 대체된다면 C,D를 가지는 새로운 스트림이 생성된다.
    - Stream<R>  map(Funtion<T, R>) : T -> R 대체
    - DoubleStream  mapToDouble(ToDoubleFuntion<T>) : T -> double 대체
    - IntStream  mapToInt(ToIntFuntion<T>) : T -> int 대체
    - LongStream  mapToLong(ToLongFuntion<T>) : T -> long 대체
    - DoubleStream  map(DoubleUnaryOperator) : double -> double 대체
    - IntStream  mapToInt(DoubleToIntFunction) : double -> int 대체
    - LongStream  mapToLong(DoubleToLongFunction) : double -> long 대체
    - Stream\<U>  mapToObj(DoubleFunction\<U>) : double -> U 대체
    - IntStream  map(IntUnaryOperator) : int -> int 대체
    - DoubleStream  mapToDouble(IntToDoubleFunction) : int -> double 대체
    - LongStream  mapToLong(IntToLongFunction) : int -> long 대체
    - Stream\<U>  mapToObj(IntFunction\<U>) : int -> U 대체
    - LongStream  map(LongUnaryOperator) : long -> long 대체
    - DoubleStream  mapToDouble(LongToDoubleFunction) : long -> double 대체
    - IntStream  mapToInt(LongToIntFunction) : long -> int 대체
    - Stream\<U>  mapToObj(LongFunction\<U>) : long -> U 대체
- asDoubleStream(), asLongStream(), boxed() 메소드
  - asDoubleStream() 메소드는 IntStream의 int 요소 또는 LongStream의 long 요소를 double 요소로 타입 변환해서 DoubleStream을 생성한다. asLongStream() 메소드는 IntStream의 int 요소를 long 요소로 타입 변환해서 LongStream을 생성한다. boxed() 메소드는 int, long, double 요소를 Integer, Long, Double 요소로 박싱해서 Stream을 생성한다.

> 정렬(sorted())

- 스트림은 요소가 최종 처리되기 전에 중간 단계에서 요소를 정렬해서 최종 처리 순서를 변경할 수 있다. 다음은 요소를 정렬하는 메소드이다. 객체 요소일 경우에는 클래스가 Comparable을 구현하지 않으면 sorted() 메소드를 호출했을 때 ClassCastException이 발생한다.
  - Stream<T>  sorted() : 객체를 Comparable 구현 방법에 따라 정렬
  - Stream<T> sorted(Comparator<T>) : 객체를 주어진 Comparator에 따라 정렬
  - DoubleStream  sorted() : double 요소를 오름차순 정렬
  - IntStream  sorted() : int 요소를 오름차순 정렬
  - LongStream  sorted() : long 요소를 오름차순 정렬
- 객체 요소가 Comparable을 구현한 상태에서 기본 비교(Comparable) 방법으로 정렬하고 싶다면 세 가지 방법 중 하나로 sorted()를 호출하면 된다.
  ```java
  sorted();
  sorted( (a, b) -> a.compareTo(b) );
  sorted( Comparator.naturalOrder() );

  //기본 비교 방법과 정반대 방법으로 정렬하고 싶다면
  sorted( (a, b) -> b.compareTo(a) );
  sorted( Comparator.reverseOrder() );
  ```
- 객체 요소가 Comparable을 구현하지 않았다면 Comparator를 매개값으로 갖는 sorted() 메소드를 사용하면 된다. Comparator는 함수적 인터페이스이므로 람다식으로 매개값을 작성할 수 있다.
  ```java
  sorted( (a, b) -> {..} );
  //{}안에는 a와 b를 비교해서 a가 크면 양수, 작으면 음수, 같으면 0을 리턴하는 코드
  ```

> 루핑(peek(), forEach())

- looping은 요소 전체를 반복하는 것을 말한다. 루핑하는 메소드에는 중간 처리 메소드인 peek(), 최종 처리 메소드인 forEach()가 있다.
- peek()는 중간 처리 단계에서 전체 요소를 루핑하면서 추가적인 작업을 하기 위해 사용한다. 최종 처리 메소드가 실행되지 않으면 지연되기 때문에 반드시 최종 처리 메소드가 호출되어야 동작한다.
- forEach()는 최종 처리 메소드이기 때문에 파이프라인 마지막에 루핑하면서 요소를 하나씩 처리한다. 다른 최종 처리 메소드를 호출하면 안된다.

> 매칭(allMatch(), anyMatch(), noneMatch())

스트림은 최종 처리 단계에서 요소들이 특정 조건에 만족하는지 조사할 수 있도록 세 가지 매칭 메소드를 제공한다. allMathch()는 모든 요소들이 매개값으로 주어진 Predicate의 조건을 만족하는지 조사하고, anyMatch()는 최소한 한 개의 요소가 매개값으로 주어진 Predicate의 조건을 만족하는지 조사한다. noneMatch()는 모든 요소들이 매개값으로 주어진 Predicate의 조건을 만족하지 않는지 조사한다.

- Stream 인터페이스 제공
  - boolean  allMatch(Predicate<T> predicate)
  - boolean  anyMatch(Predicate<T> predicate)
  - boolean  noneMatch(Predicate<T> predicate)
- IntStream 인터페이스 제공
  - boolean  allMatch(IntPredicate<T> predicate)
  - boolean  anyMatch(IntPredicate<T> predicate)
  - boolean  noneMatch(IntPredicate<T> predicate)
- LongStream 인터페이스 제공
  - boolean  allMatch(LongPredicate<T> predicate)
  - boolean  anyMatch(LongPredicate<T> predicate)
  - boolean  noneMatch(LongPredicate<T> predicate)
- DoubleStream 인터페이스 제공
  - boolean  allMatch(DoublePredicate<T> predicate)
  - boolean  anyMatch(DoublePredicate<T> predicate)
  - boolean  noneMatch(DoublePredicate<T> predicate)

> 기본 집계(sum(), count(), average(), max(), min())

집계(Aggregate)는 최종 처리 기능으로 요소들을 처리해서 카운팅, 합계, 평균값, 최대값, 최소값 등과 같이 하나의 값으로 산출하는 것을 말한다. 집계는 대량의 데이터를 가공해서 축소하는 리덕션(Reduction)이라고 볼 수 있다.
- 스트림이 제공하는 기본 집계 메소드
  - long  count() : 요소 개수
  - OptionalXXX  findFirst() : 첫 번째 요소
  - Optional<T>  max(Comparator<T>) : 최대 요소
  - OptionalXXX  max() : 최대 요소
  - Optional<T>  min(Comparator<T>) : 최소 요소
  - OptionalXXX  min() : 최소 요소
  - OptionalDouble  average() : 요소 평균
  - int, long, double  sum() : 요소 총합
  - 위 집계 메소드에서 리턴하는 OptionalXXX는 자바8에서 추가한 java.util패키지의 Optional, OptionalDouble, OptionalInt, OptionalLong 클래스 타입을 말한다. 이들은 값을 저장하는 값 기반 클래스(value-based class)이다. 객체에서 값을 얻기 위해서는 get(), getAsDouble(), getAsInt(), getAsLong()을 호출하면 된다.
- Optional 클래스
  - Optional, OptionalDouble, OptionalInt, OptionalLong 클래스들은 저장하는 값의 타입만 다를 뿐 제공하는 기능은 거의 동일하다. 단순히 집계 값만 저장하는 것이 아니라, 집계 값이 없을 경우 디폴트 값을 설정할 수 있고 집계 값만 처리하는 Consumer도 등록할 수 있다. 
  - Optional 클래스들이 제공하는 메소드
    - boolean  isPresent() : 값이 저장되어 있는 지 여부
    - T  orElse(T)
    - double  orElse(double)
    - int  orElse(int)
    - long  orElse(long) : 값이 저장되어 있지 않을 경우 디폴트 값 지정
    - void  ifPresent(Consumer | DoubleConsumer | IntConsumer | LongConsumer) : 값이 저장되어 있을 경우 Consumer 에서 처리
  - 컬렉션의 요소는 동적으로 추가되는 경우가 많다. 만약 저장된 요소가 없을 경우, 값을 계산하려 하면 NoSuchElementException이 발생한다. 예외를 피하는 방법은 세 가지다.
    - Optional객체를 얻어 isPresent() 메소드로 값 여부를 확인 후 진행
    - orElse() 메소드로 디폴트 값을 정해 놓는다.
    - ifPresent() 메소드로 값이 저장되어 있을 경우에만 값을 이용

> 커스텀 집계(reduce())

스트림은 기본 집계 메소드인 sum(), count(), average(), max(), min()을 제공하지만, 프로그램화해서 다양한 집계 결과물을 만들 수 있도록 reduce() 메소드도 제공한다. 스트림에 요소가 전혀 없을 경우 디폴트 값인 identity 매개값이 리턴된다. Operator 매개값에는 집계 처리를 위한 람다식을 대입한다.
- Stream 인터페이스 제공
  - Optional<T>  reduce(BinaryOperator<T> accumulator)
  - T  reduce(T identity, BinaryOperator<T> accumulator)
- IntStream 인터페이스 제공
  - OptionalInt  reduce(IntBinaryOperator op)
  - int  reduce(int identity, IntBinaryOperator op)
- LongStream 인터페이스 제공
  - OptionalLong  reduce(LongBinaryOperator op)
  - long  reduce(long identity, LongBinaryOperator op)
- DoubleStream 인터페이스 제공
  - OptionalDouble  reduce(DoubleBinaryOperator op)
  - int  reduce(double identity, DoubleBinaryOperator op)

> 수집(collect())

스트림은 요소들을 필터링 또는 매핑한 후 요소들을 수집하는 최종 처리 메소드인 collect()를 제공하고 있다. 이 메소드를 이용하면 필요한 요소만 컬렉션으로 담을 수 있고, 요소들을 그룹핑한 후 집계(리덕션)할 수 있다.

- 필터링한 요소 수집
  - Stream 인터페이스의 collect(Collector<T, A, R> collector) 메소드는 필터링 또는 매핑된 요소들을 새로운 컬렉션에 수집하고, 이 컬렉션 (R)을 리턴한다.
  - 매개값인 Collector(수집기)는 어떤 요소를 어떤 컬렉션에 수집할 것인지를 결정한다. 타입 파리미터 T는 요소이고, A는 누적기(accumulator)이다. R은 요소가 저장될 컬렉션이다. 즉, T요소를 A누적기가 R에 저장한다. Collector의 구현 객체는 Collectors 클래스의 다양한 정적 메소드를 이용해서 얻을 수 있다.
    - Collector<T, ?, List<T>>  toList() : T를 List에 저장
    - Collector<T, ?, Set<T>>  toSet() : T를 Set에 저장
    - Collector<T, ?, Collection<T>>  toCollection(Supplier<Collection<T>>) : T를 Supplier가 제공한 Collection에 저장
    - Collector<T, ?, Map<K, U>>  toMap(Function<T, K> keyMapper, Function<T, U> valueMapper) : T를 K와 U로 매핑해서 K를 키로, U를 값으로 Map에 저장
    - Collector<T, ?, ConcurrentMap<K, U>>  toConcurrentMap(Function<T, K> keyMapper, Function<T, U> valueMapper) : T를 K와 U로 매핑해서 K를 키로, U를 값으로 ConcurrentMap에 저장
  
    리턴값인 Collector의 누적기가 ?인 것은, Collector가 컬렉션에 요소를 저장하는 방법을 알고 있어서 누적기가 필요 없기 때문이다. Map은 스레드에 안전하지 않고, ConcurrentMap은 스레드에 안전하다.

- 사용자 정의 컨테이너에 수집하기
  - 스트림은 요소들을 List, Set, Map과 같은 컬렉션이 아니라 사용자 정의 컨테이너 객체에 수집할 수 있도록 collect() 메소드를 추가적으로 제공한다.
    - Stream 인터페이스
      - R  collect(Supplier<R>, BiConsumer<R, ?super T>, BiConsumer<R, R>)
    - IntStream 인터페이스
      - R  collect(Supplier<R>, ObjIntConsumer<R, ?super T>, BiConsumer<R, R>)
    - LongStream 인터페이스
      - R  collect(Supplier<R>, ObjLongConsumer<R, ?super T>, BiConsumer<R, R>)
    - DoubleStream 인터페이스
      - R  collect(Supplier<R>, ObjDoubleConsumer<R, ?super T>, BiConsumer<R, R>)
  
  - 첫 번째 Supplier는 요소들이 수집될 컨테이너 객체(R)를 생성하는 역할을 한다. 순차적 처리하는 싱글 스레드 스트림에서는 한 번 Supplier가 실행되고 하나의 컨테이너 객체를 생성한다. 병렬 처리하는 멀티 스레드 스트림에서는 여러 번 Supplier가 실행되고 스레드별로 여러 개의 컨테이너 객체를 생성한 뒤 최종적으로 하나의 컨테이너 객체로 결합된다.
  - 두 번째 XXXConsumer는 컨테이너 객체에 요소를 수집하는 역할을 한다. 스트림에서 요소를 컨테이너 객체에 수집할 때마다 실행된다.
  - 세 번째 BiConsumer는 컨테이너 객체를 결합하는 역할을 한다. 병렬 처리 스트림에서만 호출된다.

- 요소를 그룹핑해서 수집
  - collect() 메소드는 단순히 요소를 수집하는 기능 이외에 컬렉션의 요소들을 그룹핑해서 Map 객체를 생성하는 기능도 제공한다. collect() 호출 시 Collectors의 groupingBy() 또는 groupingByConcurrent()가 리턴하는 collector를 매개값으로 대입하면 된다. groupingByConcurrent()는 스레드에 안전한 ConcurrentMap을 생성한다.
  - Collectors의 정적 메소드
    - Collector<T, ?, Map<K, List<T>>>  groupingBy(Function<T, K> classifier) : T를 K로 매핑하고 K키에 저장된 List에 T를 저장한 Map 생성
    - Collector<T, ?, ConcurrentMap<K, List<T>>>  groupingByConcurrent(Function<T, K> classifier) : T를 K로 매핑하고 K키에 저장된 List에 T를 저장한 Map 생성
    - Collector<T, ?, Map<K, D>>  groupingBy(Function<T, K> classifier, Collector<T, A, D> collector) : T를 K로 매핑하고 K키에 저장된 D객체에 T를 누적한 Map 생성
    - Collector<T, ?, ConcurrentMap<K, D>>  groupingByConcurrent(Function<T, K> classifier, Collector<T, A, D> collector) : T를 K로 매핑하고 K키에 저장된 D객체에 T를 누적한 Map 생성
    - Collector<T, ?, Map<K, D>>  groupingBy(Function<T, K> classifier, Supplier<Map<K, D>> mapFactory, Collector<T, A, D> collector) : T를 K로 매핑하고 Supplier가 제공하는 Map에서 K키에 저장된 D객체에 T를 누적
    - Collector<T, ?, ConcurrentMap<K, D>>  groupingByConcurrent(Function<T, K> classifier, Supplier<ConcurrentMap<K, D>> mapFactory, Collector<T, A, D> collector) : T를 K로 매핑하고 Supplier가 제공하는 Map에서 K키에 저장된 D객체에 T를 누적

- 그룹핑 후 매핑 및 집계
  - Collectors.groupingBy() 메소드는 그룹핑 후, 매핑이나 집계(평균, 카운팅, 연결, 최대, 최소, 합계)를 할 수 있도록 두 번째 매개값으로 Collector를 가질 수 있다. Collectors는 mapping() 메소드 이외에도 집계를 위해 다양한 Collector를 리턴하는 메소드를 제공한다.
    - Collector<T, ?, R>  mapping(Function<T, U> mapper, Collector<U, A, R> collector) : T를 U로 매핑한 후, U를 R에 수집
    - Collector<T, ?, Double>  averagingDouble(ToDoubleFunction<T> mapper) : T를 Double로 매핑한 후, Double의 평균값을 산출
    - Collector<T, ?, Long>  counting() : T의 카운팅 수를 산출
    - Collector<CharSequence, ?, String>  joining(CharSequence delimiter) : CharSequence를 구분자(delimiter)로 연결한 String을 산출
    - Collector<T, ?, Optional<T>>  maxBy(Comparator<T> comparator) : Comparator를 이용해서 최대 T를 산출
    - Collector<T, ?, Optional<T>>  minBy(Comparator<T> comparator) : Comparator를 이용해서 최소 T를 산출
    - Collector<T, ?, Integer>  summingIng(ToIntFunction), summingLong(ToLongFunction), summingDouble(ToDoubleFunction) : Int, Long, Double 타입의 합계 산출

> 병렬 처리

병렬 처리(Prallel Operation)란 멀티 코어 CPU 환경에서 하나의 작업을 분할해서 각각의 코어가 병렬적으로 처리하는 것을 말하는데, 목적은 작업 처리 시간을 줄이기 위해서이다. 자바 8부터 병렬 처리할 수 있도록 하기 위해 병렬 스트림을 제공하기 때문에 컬렉션(배열)의 전체 요소 처리 시간을 줄여 준다.

- 동시성과 병렬성
  - 멀티 스레드는 동시성 또는 병렬성으로 실행된다. 동시성은 멀티 작업을 위해 멀티 스레드가 번갈아가며 실행하는 것이고 병렬성은 멀티 작업을 위해 멀티 코어를 이용해서 동시에 실행하는 것이다.
  - 병렬성은 데이터 병렬성과 작업 병렬성으로 구분된다.
    - 데이터 병렬성(Data parallelism)
      - 데이터 병렬성은 전체 데이터를 쪼개어 서브 데이터를 만들고 이것을 병렬 처리해서 작업을 빨리 끝내는 것을 말한다. 자바 8에서 지원하는 병렬 스트림은 데이터 병렬성을 구현한 것이다. 멀티 코어의 수만큼 대용량 요소를 서브 요소로 나누고, 각각의 서브 요소들을 분리된 스레드에서 병렬 처리시킨다.
    - 작업 병렬성(Task parallelism)
      - 작업 병렬성은 서로 다른 작업을 병렬 처리하는 것이다. 대표적인 예는 웹 서버이다. 웹 서버는 각각의 브라우저에서 요청한 내용을 개별 스레드에서 병렬로 처리한다.
- 포크조인(ForkJoin) 프레임워크
  - 병렬 스트림은 요소들을 병렬 처리하기 위해 포크조인 프레임워크를 사용한다. 병렬 스트림을 이용하면 런타임 시에 포크조인 프레임워크가 동작하는데, 포크 단계에서는 전체 데이터를 서브 데이터로 분리한다. 그리고 나서 서브 떼이터를 멀티 코어에서 병렬로 처리한다. 조인 단계에서는 서브 결과를 결합해서 최종 결과를 만들어 낸다. *(836p 그림 참고)*
  - 병렬 처리 스트림은 포크 단계에서 내부적으로 서브 요소를 나누는 알고리즘이 있다. 포크조인 프레임워크는 포크와 조인 기능 이외에 스레드풀인 ForkJoinPool을 제공한다. 각각의 코어에서 서브 요소를 처리하는 것은 개별 스레드가 해야 하므로 스레드 관리가 필요하다. 포크조인 프레임워크는 ExecutorService의 구현 객체인 ForkJoinPool을 사용해서 작업 스레드를 관리한다.

- 병렬 스트림 생성
  - 병렬 처리를 위해 코드에서 포크조인 프레임워크를 직접 사용할 수는 있지만, 병렬 스트림을 이용할 경우에는 백그라운드에서 포크조인 프레임워크가 사용되기 때문에 개발자는 매우 쉽게 병렬 처리를 할 수 있다. 병렬 스트림은 다음 두 가지 메소드로 얻을 수 있다.
    - java.util.Collection 인터페이스 - Stream  parallelStream()
    - java.util.Stream, IntStream, LongStream, DoubleStream 인터페이스 - Stream, IntSream, LongStream, DoubleStream  parallel()
  - parallelStream() 메소드는 컬렉션으로부터 병렬 스트림을 바로 리턴한다. parallel() 메소드는 순차 처리 스트림을 병렬 처리 스트림으로 변환해서 리턴한다. 

- 병렬 처리 성능
  - 요소의 수와 요소당 처리 시간
    - 컬렉션에 요소의 수가 적고 요소당 처리 시간이 짧으면 순차 처리가 오히려 병렬 처리보다 빠를 수 있다. 병렬 처리는 스레드풀 생성, 스레드 생성이라는 추가적인 비용이 발생한다.
  - 스트림 소스의 종류
    - ArrayList, 배열은 인덱스로 요소를 관리하기 때문에 포크 단계에서 요소를 쉽게 분리할 수 있다. 반면 HashSet, TreeSet은 요소 분리가 쉽지 않고, LinkedList 역시 링크를 따라가야 하므로 요소 분리가 쉽지 않다. 이 소스들은 상대적으로 병렬 처리가 늦다.
  - 코어의 수
    - 싱글 코어 CPU일 경우 순차 처리가 빠르다. 병렬 스트림을 사용할 경우 스레드의 수만 증가하고 동시성 작업으로 처리되기 때문에 결과가 좋지 않다. 코어의 수가 많을수록 병렬 작업 처리 속도는 빨라진다.

## 17. JavaFX

> JavaFX 개요

JavaFX는 크로스 플랫폼에서 실행하는 리치 클라이언트 애플리케이션(Rich Client Application)을 개발하기 위한 그래픽과 미디어 패키지를 말한다. JavaFX는 자바 7부터 JDK에 포함되어 있기 때문에 별도의 SDK 설치 없이 바로 사용할 수 있다.

JavaFX 애플리케이션에서 UI 생성, 이벤트 처리, 멀티미디어 재생, 웹 뷰 등과 같은 기능은 JavaFX API로 개발하고 이외의 기능은 자바 표준 API를 활용해서 개발할 수 있다. 멀티 스레딩과 서버 통신 기능은 자바 표준 API를 사용하면서 JavaFX에서 제공하는 풍부한 UI 기능을 활용할 수 있다는 점에서 매우 큰 장점이 될 수 있다.

JavaFX는 화명 레이아웃과 스타일, 애플리케이션 로직을 분리할 수 있기 때문에 디자이너와 개발자들이 협력해서 JavaFX 애플리케이션을 개발할 수 있는 구조를 가지고 있다. 자바 코드와 분리해서 스타일 시트(CSS)로 외관을 작성할 수 있기 때문에 그래픽 디자이너가 CSS로 작업할 동안 개발자들은 애플리케이션 로직에 더 많은 시간을 할애할 수 있다. 자바 코드에서도 레이아웃과 애플리케이션 로직을 분리하고 싶다면 레이아웃은 FXML 파일로 작성하고 애플리케이션은 자바 코드로 작성하면 된다.

- JavaFX 애플리케이션 구성 요소
  - 레이아웃
    - 자바 코드파일 또는 FXML 파일
  - 외관 및 스타일
    - CSS 파일
  - 비즈니스 로직
    - 자바 코드 파일
  - 리소스
    - 그림 파일
    - 동영상 파일
    - ...

> JavaFX 애플리케이션 개발 시작

- 메인 클래스
  - JavaFX 애플리케이션을 개발하려면 제일 먼저 메인 클래스를 작성해야 한다. JavaFX 애플리케이션을 시작시키는 메인 클래스는 추상 클래스인 javafx.application.Application을 상속받고, start() 메소드를 재정의해야 한다. 그리고 main() 메소드에서 Application의 launch() 메소드를 호출해야 한다. launch() 메소드는 메인 클래스의 객체를 생성하고, 메인 윈도우를 생성한 다음 start() 메소드를 호출하는 역할을 한다.
    ```java
    public class AppMain extends Application {
      @Override
      public void start(Stage primaryStage) throws Exception {
        primaryStage.show(); // 윈도우 보여주기
      }

      public static void main(String[] args) {
        launch(args); // AppMain 객체 생성 및 메인 윈도우 생성
      }
    }
    ```
    
    