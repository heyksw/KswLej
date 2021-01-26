using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour
{
    public float maxSpeed;
    public float jumpPower;
    bool isJump;
    Rigidbody2D rigid;

    void Awake()
    {
        isJump = true;
        rigid = GetComponent<Rigidbody2D>();
    }

    void Update()
    {
        /*//Stop Speed
        if (Input.GetButtonUp("Horizontal"))
        {
            rigid.velocity = new Vector2(rigid.velocity.normalized.x * 0.5f, rigid.velocity.y);
        }*/
        if(Input.GetButtonDown("Jump") && !isJump)
        { 
            isJump = true;
            rigid.AddForce(new Vector2(0, jumpPower), ForceMode2D.Impulse);
        }
    }
    void FixedUpdate()
    {
        //Move Speed
        float h = Input.GetAxisRaw("Horizontal");
        rigid.AddForce(new Vector2(h, 0), ForceMode2D.Impulse);

        //Max Speed
        if (rigid.velocity.x > maxSpeed)
            rigid.velocity = new Vector2(maxSpeed, rigid.velocity.y);
        if (rigid.velocity.x < maxSpeed * (-1))
            rigid.velocity = new Vector2(maxSpeed * (-1), rigid.velocity.y);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Debug.Log("Collision Entered : " + collision.gameObject.name);
        isJump = false;
    }
}
