# DreamBox 작업 시 규칙

<aside>
💡 2022/06/26 13:51 최초 작성, 미완성..

</aside>

<aside>
☝ 수정이 필요한 사항은 주간결산과 데일리 스크럼에서 언급 부탁드립니다

</aside>

*+) 표준과 차이가 있을 수 있습니다.* 

## 목차

---

- [C++와 Blueprint](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [기본](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [Reflection](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [C++ 작명 규칙](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [BP 작명 규칙](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [주석](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [조건문, 반복문](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [그 외](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
- [Git](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [commit](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [push](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [pull-request](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
- [파일 관리](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [디렉토리 구조](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
    - [Google Drive](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)

# C++/BP

## 기본

---

- 클래스 체계
    - `public` 선언 → 이후 `private` 구현
    - 선언과 정의는 각각의 파일에 분리 (`.h`, `.cpp`)
- 중괄호
    - BSD 스타일로 통일
    
    ```cpp
    void UpdateCharacterHPValue()
    **{**
       ...
    **}**
    ```
    
- 작명 기본
    
    
    - 기본적으로 **PascalCase**를 따름
        
        ```cpp
        public class AMainCharacter{...}
        int32 PlayerIndex;
        float CharacterHP;
        ```
        
    - 단, 파라미터와 함수 내 지역 변수는 CamelCase를 사용
        
        ```
        
        ```
        

## Reflection — ([참고](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61))

---

- UPROPERTY의 Category는 분류에 따라 작성하기
    
    ```cpp
    ...
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    	float CharacterHP = 100.0f;
    
    UPROPERTY(EditAnywhere, Category = "VFX")
    	UParticleSystem * ExplosionParticleSystem; 
    ...
    ```
    
- UFUNCTION, UPROPERTY의 공개범위, 수정권한
    - BP 파생 클래스에서 Read/Write가 없는 코드는 BP에 권한을 주지 않기
    - BP 파생 클래스의 디테일 패널에 보여야하는 부분만 공개하기

## C++ 작명규칙

---

- **접두사**
    - 변수 이름과 구분하기 위해 대문자 하나로 나타내는 접두사를 붙임
    1. 클래스
        - `UObject`의 하위 클래스에 붙는 접두사 **U**
        - `AActor`의 하위 클래스에 붙는 접두사 **A**
        - `SWidget`의 하위 클래스 접두사는 **S**
        - `추상 인터페이스`의 접두사는 **I** (대문자 i)
        - 그 외 클래스는 대부분 **F**
    2. 열거형
        - Enum의 접두사는 **E**
    3. boolean
        - 접두사 **b** :  `bIsDestroying`
    4. Typedef
        - 실제 타입의 접두사를 따름
        - 예시 : `typedef TArray<FMytype> FArrayOfMyTypes;`
- 변수명
    - 명사 형태로 작성
    - 파라미터나 반환값이 `bool`이라면 접두사 **b**를 붙임
- 함수명
    - 주로 동사로 작성하나, 반환값을 설명할 수도 있음
    - 반환 타입이 `bool`이라면, 질문 형태로 작성
        
        → 예시 : `IsVisible()` , `ShouldDestroyProjectile()`
        
- 종합 예시 (UE4 Docs)
    
    ```cpp
    float TeaWeight;
    int32 TeaCount;
    bool bDoesTeaStink;
    FName TeaName;
    FString TeaFriendlyName;
    UClass* TeaClass;
    USoundCue* TeaSound;
    UTexture* TeaTexture;
    ```
    

## Blueprint 작명 규칙

---

- 기본적으로 내부 이벤트, 함수, 변수 등의 작명 규칙은 C++과 동일
- C++ 클래스 파생 BP는 앞에 `BP_`를 붙임
    - 그 외에도 사용자 임의 BP는 모두 포함 (Widget, AnimBP etc..)
- 이외의 파일은 유형에 따라 접두사를 붙임
    
    ```cpp
    - Niagara System : **NS**
    - Particle System : **PS**
    - Animation Montage : **AM**
    - Struct : **S**
    - Enum : **E**
    - DataSheet : **D
    ...** 
    ```
    
    ***+) 애매한 것은 바로 Slack이나 Trello에 올려주세요!!!!!***
    

## 주석

---

- 주석은 ‘한글로' 작성
- 클래스
    - 각 클래스별 주석은 `/**/`로, 아래 양식에 맞게 작성
    
    ```cpp
    /*
     - Name        : AFire
     - Descirption : FireHose의 물에 닿으면 꺼지는 불 액터
     - Date        : 2022/06/22 LJH
    */
    
    UCLASS(Category = "FireFighter")
    class LISTENSERVERSTUDY_API AFire : public AActor
    {
    ```
    
- 함수 선언부
    - 헤더파일의 선언부에만 작성
    - 위에 한줄 주석`//`을 작성
        
        ```cpp
        //장애물의 위치를 특정 초 단위로 업데이트 한다. 
        void AObstacleBase::UpdateObstacleLocation()
        { . . . }
        ```
        
    - 반환형과 파라미터에 대한 설명도 포함
        
        ```cpp
        // 캐릭터의 방어력,, 을 기반으로 실제 받는 데미지를 계산해서 반환
        // Damage : ~~
        // FDamageEvent : ~~
        // DamageCause : ~~
        float AMainCharacter::Getamage(float Damage, struct FDamageEvent, AActor* DamageCauser)
        {
        	...
        	return FinalDamage;
        }
        ```
        
- 함수 정의부
    - 각 라인에 맞게 간결히 작성
    - 라인이 긴 부분은 위에 한줄 주석으로 작성
        
        ```cpp
        ...
        void AMainCharacter::StartSlide()
        {
          //캐릭터가 ~ ,, 하면 강재 종료
        	if (GetCharacterMovement()->IsCrouching() || bIsDead || bIsRagdoll || !bCanSlide) return;
        
        	StopJump(); 
          StopAim(); //슬라이드를 위해 점프와 조준을 취소
        	GetCharacterMovement()->MaxWalkSpeedCrouched = CharacterWalkSpeed;
        
        	//UE_LOG(LogTemp, Warning, TEXT("Crouch"));
        	ACharacter::Crouch();
        }
        ```
        

## 조건문과 반복문

---

- **조건문**
    - 한 줄을 제외한 모든 경우에 중괄호를 붙임
    - 들여쓰기는 반드시 지키기
    
    ```cpp
    if(IsCharacaterDead()) return; 
    else 
    {
    	 . . .
    }
    ```
    
- **반복문**
    - 단순 idx 접근을 제외하면, 변수명 `i`, `j`, `k`는 지양
    - 들여쓰기 필수
    - [auto, 범위 기반 반복문](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61)
- Switch
    - 들여쓰기 필수
    - `defaults`에도 내용 기입 (예외처리문 등)

## 그 외

---

- **C++ 최신 문법**
    - `auto`의 사용을 금함
    - NULL을 `nullptr`로 대체
    - 범위 기반 반복문 허용

---

---

# Git

## commit

---

- commit은 task의 완성 단위로 진행
    
    *→ 즉, 작동하지 않는 코드나 critical한 오류가 발생한 코드는 commit을 금지*
    
- commit 메시지 — ([참고](https://www.notion.so/DreamBox-6f888b4121644753998eaf3befdefc61))
    - 타입
        
        ```java
        [feat] : 기능 추가
        [fix] : 버그 픽스
        [docs] : 문서 수정
        [style] : 포맷, 세미콜론 수정
        [refactor] : 코드 리팩토링
        [test] : 테스트 코드 추가
        [chore] : 빌드 관련 업무 수정
        ```
        
    - 제목 (head)
        - 50자를 넘기지 않고 대문자로 시작
        - 서술어가 아닌 명사로 마무리
        - 과거시제가 아닌 명령문으로 작성
        - “.” 과 같은 마침표는 찍지 않음
    - 본문 (body)
        - 선택 사항
        - 부연설명과 커밋의 이유가 주된 내용
    - 꼬리글 (footer)
        - 선택 사항
        - issue tracker id

## push

---

- `.gitignore`
    
    ```
    # Visual Studio 2015 user specific files
    .vs/
    
    # Compiled Object files
    *.slo
    *.lo
    *.o
    *.obj
    
    # Precompiled Headers
    *.gch
    *.pch
    
    # Compiled Dynamic libraries
    *.so
    *.dylib
    *.dll
    
    # Fortran module files
    *.mod
    
    # Compiled Static libraries
    *.lai
    *.la
    *.a
    *.lib
    
    # Executables
    *.exe
    *.out
    *.app
    *.ipa
    
    # These project files can be generated by the engine
    *.xcodeproj
    *.xcworkspace
    *.sln
    *.suo
    *.opensdf
    *.sdf
    *.VC.db
    *.VC.opendb
    
    # Precompiled Assets
    SourceArt/**/*.png
    SourceArt/**/*.tga
    
    # Binary Files
    Binaries/*
    Plugins/*/Binaries/*
    
    # Builds
    Build/*
    
    # Whitelist PakBlacklist-<BuildConfiguration>.txt files
    !Build/*/
    Build/*/**
    !Build/*/PakBlacklist*.txt
    
    # Don't ignore icon files in Build
    !Build/**/*.ico
    
    # Built data for maps
    *_BuiltData.uasset
    
    # Configuration files generated by the Editor
    Saved/*
    Content/Asset/*
    
    # Compiled source files for the engine to use
    Intermediate/*
    Plugins/*/Intermediate/*
    
    # Cache files for the editor to use
    DerivedDataCache/*
    ```
    
- 강제 push 절대 금지
    
    ```java
    git push origin +master
    git push origin +develop_firefighter
    ```
    

## pull-request

---

- -

---

---

# 파일 관리

---

- 디렉토리 구조
    - `/Source`
        - 디렉토리 구조
            
            ```
            - Source/MyProject
               - Common
                  - private
                  - public
               - Astronaut
                  - private
                  - public
               - FireFighter
            	    - private
                  - public
               - Judge
            	    - private
                  - public
              
            ```
            
            - public 폴더 내 헤더파일(.h)
            - private 폴더 내 소스파일(.cpp)
    - `/Content`
        - 디렉토리 구조
            
            ```
            - Content
               - Judge
                  - 
               - FireFighter
                  - Character
                  - Map
               - Astronaut
                  - 
               - Common
                  - 
               - Asset      //모든 에셋이 포함
                  - Common
                  - FireFighter
                  - Judge
                  - Astronaut
                  - ...
            ```
            
        - 각 직업별 폴더 내 **사용자 정의 `.uasset`**를 다음과 같이 분류
            
            ```
            1. Actor - 사용자 정의 Actor (주로 prop)
            2. Character - NPC와 PlayerCharacter
            3. Effect - Particle, Niagara 등
            4. Sound - 사운드 관련 모든 파일 (원본 파일 미포함)
            5. Material - 머티리얼과 텍스쳐 
            6. Map - 레벨
            7. UI - 위젯BP
            8. Data - 데이터 파일(.csv 등), 구조체, 열거형
            ```
            
            *→ 단, 사용자가 외부에서 받는 100mb 이상의 파일(3D 모델, 사운드 등)은 
                 에셋으로 포함. `./Content/Asset/직업명` 디렉토리에 별도로 분류*
            
        - Common 디렉토리 내에는 공통으로 사용하는 요소
            - 주로 GameInstance, Lobby레벨 등
- Google Drive — ([링크](https://drive.google.com/drive/folders/1ISVOUreA06DZhIyYnvQvMi5AxSyhstUr))
    - 본 클라우드 저장소는 대용량 파일 (주로 에셋) 등을 공유하기 위함
    - Asset 폴더 내 상대 경로 그대로 저장할 것
    - 항상 Stable한 상태로 유지 → 수정된 에셋 중, 작동하지 않는 파일은 추가하지 않음

---

---

## 참고할 자료

---

- UE4 Docs → 일부 다른 내용이 있음
    
    [코딩 표준](https://docs.unrealengine.com/4.27/ko/ProductionPipelines/DevelopmentSetup/CodingStandard/)
    
- Reflection
    
    [UE4 C++와 블루프린트 연동 기본 -1. UPROPERTY()](https://darkcatgame.tistory.com/62)
    
- Commit Message
    
    [[Git] Git Commit Message Convention 정리](https://youngest-programming.tistory.com/550)
