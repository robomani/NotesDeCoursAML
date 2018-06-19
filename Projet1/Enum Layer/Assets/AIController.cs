using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum BehaviourState
{
    Idle,
    Flee,
    Chase,
    Attack,
    EatRamenSoup,

    Count
}

public class AIController : MonoBehaviour
{
    private BehaviourState m_State;
    public int HP = 100;

    private void Start()
    {
        m_State = BehaviourState.Idle;
    }

    private void Update()
    {
        if (CompareState(BehaviourState.Idle))
        {
            UpdateIdle();
        }

        if (CompareState(BehaviourState.EatRamenSoup))
        {
            UpdateEatRamenSoup();
        }
    }

    private void UpdateIdle()
    {
        if (10 < 15)
        {
            m_State = BehaviourState.Attack;
        }
    }
    private void UpdateFlee()
    {

    }
    private void UpdateChase()
    {

    }
    private void UpdateAttack()
    {

    }
    private void UpdateEatRamenSoup()
    {

    }

    private void ChangeState(BehaviourState i_State)
    {
        m_State = i_State;
        switch (m_State)
        {
            case BehaviourState.Idle:
                break;
            case BehaviourState.Flee:
                break;
            case BehaviourState.Chase:
                break;
            case BehaviourState.Attack:
                break;
            case BehaviourState.EatRamenSoup:
                {
                    if (i_State != BehaviourState.EatRamenSoup)
                    {
                        //Call eatramensup animation
                       
                    }
                    break;
                }
            case BehaviourState.Count:
                break;
            default:
                break;
        }
    }

    private bool CompareState(BehaviourState i_State)
    {
        return i_State == m_State;
    }

    private void ReceiveDamage(int i_Damage)
    {
        HP -= i_Damage;
        if (HP < 10)
        {
            m_State = BehaviourState.EatRamenSoup;
        }
    }
}
