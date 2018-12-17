## LDEvaluationTool Refactorying
## 주 변경점

 -  **코드 구조 변경**
 
 ![enter image description here](https://lh3.googleusercontent.com/Iwe5hHf5yzGY_1gXZWNKkvyeM6C8LMSyDlG4afG7yRMB4rCCrsO9VAZ_z74a_zonLNEZ8DD1ZSYr)
'''	
기존 EvaluateLD 함수에 과도하게 몰려있던 기능들을 모두 분산시켰습니다.  
파일 입력~결과 출력까지의 모든 Process를 Phase 1 ~ 4로 정의하여 각 Phase#.h 에 관련된 함수들끼리 모아두었습니다.  
main함수를 Function Call의 중심으로 하여 각 Phase의 결과물이 다음 Phase의 input으로 들어가게 됩니다.  

-  **상속, 다형성**
 
 ![enter image description here](https://lh3.googleusercontent.com/3TXj1QDtUi_uI1XROTv_YzWU71csffoyVAjsLR51S6vgZudxBDVS7MBcqsSpkVY6Xj7OxBD3Pnwt)

기존 코드의 Annotation과 Data(LogLD) 클래스는 유사한 멤버 변수와 함수를 다수 가지고 있었습니다.  
이러한 중복되는 요소들을 상위 클래스에서 상속받아 코드를 좀더 간소화 시킬 수 있었습니다.  
또한 데이터를 로드하거나 선을 그리는 등의 동작들이 기존에는 한 함수에서 동일한 코드를 두번 중복하여 처리했습니다.  
이러한 중복을 없애기 위해 템플릿 함수를 이용하여 매개변수만 변경하여 두번 호출하는 방법으로 변경하였습니다.  
	  
	
 -  **네이밍 규칙 통일**
 
![enter image description here](https://lh3.googleusercontent.com/D3jwk52vOdCaYP6EQ041Q1OR0rEX53nZB002It5OnsbM5wKzSF-obqYIHi89f4MSsKEhoDEpgGei)
	
함수, 변수, 전역변수(Threshold)들의 네이밍을 통일했습니다.  
	모든 단어간 구분은 _ 기호를 사용하며,  
	변수는 모두 소문자,  
	함수는 각 단어의 첫글자를 대문자,  
	전역변수(Threshold)들은 모두 대문자를 사용하여 구분하기 쉽도록 하였습니다.  
	![enter image description here](https://lh3.googleusercontent.com/0idDpNCwYjccOLIBLsWvOJSS3BWifmYs4YX6iwEmlGs2lxZ1yqgJBHTawiTA4Jt88RdBpNq3Vv_J)
	
또한 CALSS나 datas 같이 오타나 애매한 표현을 수정하였으며,  
	마지막으로 Annotation와 대응되는 의미인 Data가 포함된 변수,함수명들을 더 명확한 의미인 LogLD로 일괄 변경하였습니다.

 - **전역변수 선언을 통한 파라미터 개수 축소**

![enter image description here](https://lh3.googleusercontent.com/CAwPqE8TEukNXSlYUbUwFfJMYHf7EKA7gdMiSBkOo_g7XTplKyWYvZNJ4u_Bw0DUF1QSfjBdGLN9)
	
각종 Threshold들을 전역변수로 변경하여 프로그램 어디에서나 이 변수 값들에 접근 할 수 있도록 하였습니다. 또한 결과값이 저장되는 Performance 클래스 객체들 역시 전역변수로 변경하여 Function Call 위주의  플로우에서 전달되는 파라미터의 개수를 간소화시켰습니다.
	
 -  **Matching 알고리즘 변경**

기존 알고리즘 대신 Hungarian Assignment를 사용한 Matching 알고리즘으로 변경하였습니다.
LogLD Set과 Annotation Set 내의 모든 선 조합에서 가장 높은 Cost를 가지는 조합의 최적해를 구할 수 있습니다.
이 변경으로 4125개의 샘플 중 7개의 샘플에서 매칭 결과가 변했습니다. 해당 내용은 match_change.txt 파일에서 확인하실 수 있습니다.


 -  **추가 Parameters & 디버깅용 옵션**
 
![enter image description here](https://lh3.googleusercontent.com/0VKDjSlY2hWIknKU6jBL8t8hmjpu3Z1kIiKatCwaR1bxkCSFzFnN7B9W2ECluyas2gm8Evazb4-7)


기존에 지정 가능했던 Threshold 외에도, 알고리즘의 상수값이나 함수 내부에 선언된 정수값 들을 바깥으로 빼냈습니다. 이러한 값들에 따른 변화를 관찰해야 할 때 유용할 것이라고 판단했습니다.

또한 Annotation Line의 전처리(임계 길이 이하의 선들을 Ambiguous로 처리) 과정 역시 On/Off 가능하게 변경하였습니다.



![enter image description here](https://lh3.googleusercontent.com/7419ZU2svP9flnSleQGl7MGIBcFIQc9Vfae8UHSLht-Mh6ULOdVSQEjpFhKS1zIQc35HMUropNnF)


마지막으로 디버깅 Image 표시 옵션을 추가하였습니다.
Annotation, LogLD, Matched Point에 대한 표시 여부를 각각 선택할 수 있으며,
각 Line들의 색상 역시 Parameter 창에서 변경 가능하도록 변경하였습니다.


 - **버그 수정**

기존 코드에 존재하는 3가지 버그를 수정하였습니다.

  1) Sloped Threshold가 수직선에서 비정상 작동하는 현상을 수정. 	
   2) Match 알고리즘에서 특정 상황 (LogLD가 비교 대상인 Annotation의 Y축 범위를 초과할 때) 일 때,
   LogLD의 양 끝 점이 카운트 되지 않는 현상을 수정. 	
     3) Float 형의 Threshold 값이 비교 연산시 같은 값의 Double형 변수을 걸러내지 못하는 현상
    수정 (ex. (Float)0.7 > (double)0.7은 True가 반환됩니다.)

버그 수정에 의한 결과의 변화는 result_change.txt에 기록해 두었습니다.

 - **기타**

Evaluate Function에서 매크로 함수를 사용하여 코드 가독성을 약간 높였습니다.
Slope Threshold 계산 과정의 일부를 Annotation 클래스의 멤버 함수로 변경하였습니다.(Sin값 반환까지의 과정)


