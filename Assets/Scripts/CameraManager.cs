using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// ksw
public class CameraManager : MonoBehaviour
{
    public GameObject target;   //카메라가 따라갈 대상
    public float moveSpeed; //카메라 이동 속도
    private Vector3 targetPosition; //대상의 현재 위치 값

    //카메라가 움직일 범위의 BoxCollider
    public BoxCollider2D bound;

    //Box Collider 영역의 최소 최대 xyz값을 지님
    private Vector3 minBound;
    private Vector3 maxBound;

    //카메라의 반 너비, 반 높이 값을 지니는 변수
    private float halfWidth;
    private float halfHeight;

    //카메라의 반 높이 값을 구할 속성을 이용하기 위한 변수
    private Camera theCamera;

    private void Awake()
    {
        
    }


    // Start is called before the first frame update
    void Start()
    {
        theCamera = GetComponent<Camera>();
        minBound = bound.bounds.min;
        maxBound = bound.bounds.max;

        halfHeight = theCamera.orthographicSize;
        halfWidth = halfHeight * Screen.width / Screen.height;  //반 너비를 구하기 위한 공식
    }

    // Update is called once per frame
    void Update()
    {
        if(target.gameObject != null)
        {
            targetPosition.Set(target.transform.position.x, target.transform.position.y, this.transform.position.z);
            //Lerp는 A값과 B값 사이의 선형보간으로 중간 값을 리턴한다. 1초에 moveSpeed만큼 이동
            this.transform.position = Vector3.Lerp(this.transform.position, targetPosition, moveSpeed * Time.deltaTime);    
        }

        //카메라를 clamped 범위안에 가두기
        float clampedX = Mathf.Clamp(this.transform.position.x, minBound.x + halfWidth, maxBound.x - halfWidth);
        float clampedY = Mathf.Clamp(this.transform.position.y, minBound.y + halfHeight, maxBound.y - halfHeight);

        this.transform.position = new Vector3(clampedX, clampedY, this.transform.position.z);
    }
}
